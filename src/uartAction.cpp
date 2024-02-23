#include "uart.h"
#include "MACStepper.h"

#include "uartAction.h"
//#include "uart.h"

// TODO: Implement the functions defined in uartAction.h
void setCurrentDegree(motorSettings& motor){
    motor.motor0currentDegree += motor.motor0degree;
    motor.motor1currentDegree += motor.motor1degree;
    motor.motor2currentDegree += motor.motor2degree;
    motor.motor3currentDegree += motor.motor3degree;
    motor.motor4currentDegree += motor.motor4degree;
}

void setCurrentDegreeGo(motorSettings& motor){
    motor.motor0currentDegree += motor.motor0estDegree;
    motor.motor1currentDegree += motor.motor1estDegree;
    motor.motor2currentDegree += motor.motor2estDegree;
    motor.motor3currentDegree += motor.motor3estDegree;
    motor.motor4currentDegree += motor.motor4estDegree;
}

void moveMotor(motorSettings& motor){
    if(motor.motor0degree != 0){
        prepareMovement(0, motor.motor0degree);
    }
    if(motor.motor1degree != 0){
        prepareMovement(1, motor.motor1degree);
    }
    if(motor.motor2degree != 0){
        prepareMovement(2, motor.motor2degree);
    }
    if(motor.motor3degree != 0){
        prepareMovement(3, motor.motor3degree);
    }
    if(motor.motor4degree != 0){
        prepareMovement(4, motor.motor4degree);
    }
    setCurrentDegree(motor);
    runAndWait();
    Serial.println("<1>");
}

void goMotor(motorSettings& motor){
    motor.motor0estDegree = motor.motor0degree - motor.motor0currentDegree;
    motor.motor1estDegree = motor.motor1degree - motor.motor1currentDegree;
    motor.motor2estDegree = motor.motor2degree - motor.motor2currentDegree;
    motor.motor3estDegree = motor.motor3degree - motor.motor3currentDegree;
    motor.motor4estDegree = motor.motor4degree - motor.motor4currentDegree;
    if((motor.motor0estDegree) != 0){
        Serial.println("<"+String(motor.motor0estDegree)+">");
        prepareMovement(0, (motor.motor0estDegree));
        motor.isMotorMoving = true;
    }
    if((motor.motor1estDegree) != 0){
        Serial.println("<"+String(motor.motor1estDegree)+">");
        prepareMovement(1, (motor.motor1estDegree));
        motor.isMotorMoving = true;
    }
    if((motor.motor2estDegree) != 0){
        Serial.println("<"+String(motor.motor2estDegree)+">");
        prepareMovement(2, (motor.motor2estDegree));
        motor.isMotorMoving = true;
    }
    if((motor.motor3estDegree) != 0){
        Serial.println("<"+String(motor.motor3estDegree)+">");
        prepareMovement(3, (motor.motor3estDegree));
        motor.isMotorMoving = true;
    }
    if((motor.motor4estDegree) != 0){
        Serial.println("<"+String(motor.motor4estDegree)+">");
        prepareMovement(4, (motor.motor4estDegree));
        motor.isMotorMoving = true;
    }
    if(motor.isMotorMoving == true){
        runAndWait();
        motor.isMotorMoving = false;
        setCurrentDegreeGo(motor);
    }
    Serial.println("<1>");
}

void missionMotor(motorSettings& motor, messageProtocol& message){
    //mesajın içinde kaç virgül olduğunu buluyoruz ve bu virgüllerin indexlerini buluyoruz.
    int messageLength = message.message.length();
    int index = 0;
    int commaCount = 0;
    int commaIndex[messageLength];
    while(index < messageLength){
        if(message.message[index] == message.separatorChar){
            commaIndex[commaCount] = index;
            commaCount++;
        }
        index++;
    }
    motor.missionNumber = message.message.substring(commaIndex[0]+1,commaIndex[1]).toInt();
    for (int i = 0; i < motor.missionNumber; i++){
        motor.motor0degree = message.message.substring(commaIndex[5*i+1]+1,commaIndex[5*i+2]).toInt();
        motor.motor1degree = message.message.substring(commaIndex[5*i+2]+1,commaIndex[5*i+3]).toInt();
        motor.motor2degree = message.message.substring(commaIndex[5*i+3]+1,commaIndex[5*i+4]).toInt();
        motor.motor3degree = message.message.substring(commaIndex[5*i+4]+1,commaIndex[5*i+5]).toInt();
        motor.motor4degree = message.message.substring(commaIndex[5*i+5]+1,commaIndex[5*i+6]).toInt();
        Serial.println("<GOREV tetiklendi>");
        Serial.print("<motor0degree: "+String(motor.motor0degree)+">");
        Serial.print("<motor1degree: "+String(motor.motor1degree)+">");
        Serial.print("<motor2degree: "+String(motor.motor2degree)+">");
        Serial.print("<motor3degree: "+String(motor.motor3degree)+">");
        Serial.print("<motor4degree: "+String(motor.motor4degree)+">");
        goMotor(motor);
    }
    Serial.println("<1>");
}

void hizivmeAyarla(motorSettings& motor , messageProtocol& message){
    //mesajın içinde kaç virgül olduğunu buluyoruz ve bu virgüllerin indexlerini buluyoruz.
    int messageLength = message.message.length();
    int index = 0;
    int commaCount = 0;
    int commaIndex[messageLength];
    while(index < messageLength){
        if(message.message[index] == message.separatorChar){
            commaIndex[commaCount] = index;
            commaCount++;
        }
        index++;
    }
    int motorNo = message.message.substring(commaIndex[0]+1,commaIndex[1]).toInt();
    int hiz = message.message.substring(commaIndex[1]+1,commaIndex[2]).toInt();
    int ivme = message.message.substring(commaIndex[2]+1,commaIndex[3]).toInt();
    setAccelandSpeed(motorNo, ivme, hiz);
    Serial.println("<HIZIVME Ayarlandi>");
}

void offsetMotor(motorSettings& motor){
    motor.motor0currentDegree = 0;
    motor.motor1currentDegree = 0;
    motor.motor2currentDegree = 0;
    motor.motor3currentDegree = 0;
    motor.motor4currentDegree = 0;
}



