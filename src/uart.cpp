#include "uart.h"
#include "uartAction.h"
#include "MACStepper.h"
messageProtocol message;
messageProtocol *messagePtr = &message;

motorSettings motor;
motorSettings *motorPtr = &motor;

void uartInit(void){
  Serial.begin(9600);
}

void motorReset(void){
    motorPtr->motor0degree = 0;
    motorPtr->motor1degree = 0;
    motorPtr->motor2degree = 0;
    motorPtr->motor3degree = 0;
    motorPtr->motor4degree = 0;
}

void messageReset(void){
    messagePtr->message = "";
    messagePtr->messageComplete = false;
    messagePtr->dataFlow = false;
}

void serialEvent(void){
    //messagePtr pointerını kullanarak messageProtocol struct'ına erişiyoruz.
    // serialEvent() fonksiyonu serial porttan gelen verileri okuyor ve message.message değişkenine atıyor.
    while(Serial.available()){
        char inChar = (char)Serial.read();
        if(inChar == messagePtr->startChar){
            messagePtr->message = "";
            messagePtr->messageComplete = false;
            messagePtr->dataFlow = true;
        }
        else if(inChar == messagePtr->endChar){
            messagePtr->messageComplete = true;
            messagePtr->dataFlow = false;
            //Serial.println(messagePtr->message);
            messageParser();
            messageReset();
            //Serial.write(messagePtr->message.c_str());
        }
        else{
            messagePtr->message += inChar;
        }
    }
    
    //messageParser();
}

void messageParser(void){
    if(messagePtr->message == "BASLA"){
        Serial.println("<BASLA tetiklendi>");
        Serial.println("<2>");
        moveMotor(*motorPtr);
        motorReset();
    }
    else if(messagePtr->message == "KONUMAGIT"){
        Serial.println("<KONUMAGIT tetiklendi>");
        Serial.println("<2>");
        goMotor(*motorPtr);
        motorReset();
    }
    else if(messagePtr->message == "DUR"){
        Serial.println("<DUR tetiklendi>");
    }
    else if(messagePtr->message == "SIFIRLA"){
        Serial.println("<SIFIRLA tetiklendi>");
        offsetMotor(*motorPtr);
    }
    else if(messagePtr->message == "SAG"){
        Serial.println("<SAG tetiklendi>");
    }
    else if(messagePtr->message == "SOL"){
        Serial.println("<SOL tetiklendi>");
    }
    else if(messagePtr->message.substring(0,7) == "HIZIVME"){
        Serial.println("<HIZIVME tetiklendi>");
        hizivmeAyarla(*motorPtr, *messagePtr);
    }
    else if(messagePtr->message.substring(0,5) == "GOREV"){
        Serial.println("<GOREV Basliyor>");
        Serial.println("<2>");
        missionMotor(*motorPtr, *messagePtr);
    }
    else if(messagePtr->message.substring(0,6) == "AYARLA"){
        //mesajın içinde 5 virgül olmalı bu virgüllerin indexlerini buluyoruz.
        int index = 0;
        int commaCount = 0;
        int commaIndex[5];
        while(commaCount < 5){
            if(messagePtr->message[index] == messagePtr->separatorChar){
                commaIndex[commaCount] = index;
                commaCount++;
            }
            index++;
        }
        int messageLength = messagePtr->message.length();
        motorPtr->motor0degree = messagePtr->message.substring(commaIndex[0]+1,commaIndex[1]).toInt();
        motorPtr->motor1degree = messagePtr->message.substring(commaIndex[1]+1,commaIndex[2]).toInt();
        motorPtr->motor2degree = messagePtr->message.substring(commaIndex[2]+1,commaIndex[3]).toInt();
        motorPtr->motor3degree = messagePtr->message.substring(commaIndex[3]+1,commaIndex[4]).toInt();
        motorPtr->motor4degree = messagePtr->message.substring(commaIndex[4]+1,messageLength).toInt();
        Serial.println("<AYARLA tetiklendi>");
        // Serial.print("motor0degree: "+messagePtr->message.substring(commaIndex[0]+1,commaIndex[1])+"\n");
        // Serial.print("motor1degree: "+messagePtr->message.substring(commaIndex[1]+1,commaIndex[2])+"\n");
        // Serial.print("motor2degree: "+messagePtr->message.substring(commaIndex[2]+1,commaIndex[3])+"\n");
        // Serial.print("motor3degree: "+messagePtr->message.substring(commaIndex[3]+1,commaIndex[4])+"\n");
        // Serial.print("motor4degree: "+messagePtr->message.substring(commaIndex[4]+1,messageLength)+"\n");
        Serial.println("<motor0degree: "+String(motorPtr->motor0degree)+">");
        Serial.println("<motor1degree: "+String(motorPtr->motor1degree)+">");
        Serial.println("<motor2degree: "+String(motorPtr->motor2degree)+">");
        Serial.println("<motor3degree: "+String(motorPtr->motor3degree)+">");
        Serial.println("<motor4degree: "+String(motorPtr->motor4degree)+">");
    }
    else if(messagePtr->message == "BILGI"){
        sendInfo();
    }
    else if(messagePtr->message == "BILGI2"){
        Serial.println("<BILGI2 tetiklendi>");
        Serial.println("<motor0currentDegree: "+String(motorPtr->motor0currentDegree)+">");
        Serial.println("<motor1currentDegree: "+String(motorPtr->motor1currentDegree)+">");
        Serial.println("<motor2currentDegree: "+String(motorPtr->motor2currentDegree)+">");
        Serial.println("<motor3currentDegree: "+String(motorPtr->motor3currentDegree)+">");
        Serial.println("<motor4currentDegree: "+String(motorPtr->motor4currentDegree)+">");
    }
    
    else{
        Serial.println("<Hatalı komut>");
    }
}