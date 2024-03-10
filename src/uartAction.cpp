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
void mehter(motorSettings& motor){
    // motor1 acilarini tutan liste
    int motor1Acilar[] = {0, 10, 20, 30, 30, 30, 20, 10, 0, 0, 0, -10, -20, -30, -30, -30, -20, -10, 0,0, 10, 20, 30, 30, 30, 20, 10, 0, 0, 0, -10, -20, -30, -30, -30, -20, -10, 0, 0, 0, 0, 0, 0, 0, 30, -30, 30, -30 , 0,0,0,30,-30,30,-30,0,0, 0, 0, 0, 0, 0, 0, 30, 30, 30, 30, 30, 30, -30, -30, -30, -30, -30, -30, 0, 0, 0, 0, 0, 0,0};
    // motor2 acilarini tutan liste
    int motor2Acilar[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 45, -30, 0, 0,45,45,45,45,45,0,45,45,45,45,45,0,0, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0,0};
    // motor3 acilarini tutan liste
    int motor3Acilar[] = {0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0,45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 0, -45, 30, 0, 0,45,45,45,45,45,0,-45,-45,-45,-45,-45,0,0, 70, 90, 50, 90, 50, 70, 70, 90, 50, 90, 50, 70, 70, 90, 50, 90, 50, 70, 70, 90, 50, 90, 50, 70,0};
    // motor4 acilarini tutan liste
    int motor4Acilar[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0};
    //motor5 acilarini tutan liste
    int motor5Acilar[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,30, 30, 30, 30, 45, 30, 30, 30, 30, 45, 30, 30, 30, 30, 45, 30, 30, 30, 30, 45, 30, 90, 90, 0, 0,0,0,0,0,0,0,90,90,90,90,90,0,0, 0, -20, 20, -20, 20, 0, 0, -20, 20, -20, 20, 0, 0, -20, 20, -20, 20, 0, 0, -20, 20, -20, 20, 0,0};
    //motor1 hizlari listesi
    int motor1Hizlar[] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 200, 200, 200, 200, 200, 200, 200, 200, 150, 250, 250, 250,50,50,50,50,50,50,50,50,50,50,50,50,50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,50};
    //motor2 hizlari listesi
    int motor2Hizlar[] = {250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250,250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 150, 250, 250, 250,250,250,250,250,250,250,250,250,250,250,250,250,250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250,250};
    //motor3 hizlari listesi
    int motor3Hizlar[] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,20,20,20,20,20,20,20,20,20,20,20,20,20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,20};
    //motor4 hizlari listesi
    int motor4Hizlar[] = {250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250,250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 50, 250, 250, 250, 250,250,250,250,250,250,250,250,250,250,250,250,250,250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250,250};
    //motor5 hizlari listesi
    int motor5Hizlar[] = {250, 200, 200, 200, 50, 50, 200, 200, 200, 50, 50, 200, 200, 200, 50, 50, 200, 200, 50,200, 200, 200, 200, 50, 50, 200, 200, 200, 50, 50, 200, 200, 200, 50, 50, 200, 200, 200, 200, 50, 150, 250, 250, 250,250,250,250,250,250,250,250,250,250,250,250,250,20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,20};
    //motor1 ivmeleri listesi
    int motor1Ivmeler[] = {1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700,1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700,1700,1700,1700,1700,1700,1700,1700,1700,1700,1700,1700,1700,1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700,1700};
    //motor2 ivmeleri listesi
    int motor2Ivmeler[] = {2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 1500, 3000, 4000, 4000,2000,2000,2000,2000,2000,1700,1700,1700,1700,1700,1700,1700,2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,2000};
    //motor3 ivmeleri listesi
    int motor3Ivmeler[] = {850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850,850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 850, 3000, 3000, 3000, 850, 850, 3000, 3000, 3000, 3000, 850, 1500, 3000, 3000, 3000,850,850,850,850,850,850,850,850,850,850,850,850,250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250,250};
    //motor4 ivmeleri listesi
    int motor4Ivmeler[] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000,4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000,4000};
    //motor5 ivmeleri listesi
    int motor5Ivmeler[] = {4000, 3200, 3200, 3200, 1600, 1600, 3200, 3200, 4000, 1600, 1600, 3200, 3200, 3200, 1600, 1600, 3200, 3200, 1600,3200, 3200, 3200, 3200, 1000, 1000, 3200, 3200, 4000, 1000, 1000, 3200, 3200, 3200, 1000, 1000, 3200, 3200, 1000, 1000, 1000, 1500, 4000, 4000, 4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250,250};
    //Serial.println("<SESON>");
    for(int i = 0; i < 82; i++){
        motor.motor0degree = motor1Acilar[i];
        motor.motor1degree = motor2Acilar[i];
        motor.motor2degree = motor3Acilar[i];
        motor.motor3degree = motor4Acilar[i];
        motor.motor4degree = motor5Acilar[i];
        setAccelandSpeed(0, motor1Ivmeler[i], motor1Hizlar[i]);
        setAccelandSpeed(1, motor2Ivmeler[i], motor2Hizlar[i]);
        setAccelandSpeed(2, motor3Ivmeler[i], motor3Hizlar[i]);
        setAccelandSpeed(3, motor4Ivmeler[i], motor4Hizlar[i]);
        setAccelandSpeed(4, motor5Ivmeler[i], motor5Hizlar[i]);
        goMotor(motor);
    }

    //Serial.println("<SESOFF>");
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
void missionMotorWithAccel(motorSettings& motor, messageProtocol& message){ // Hatalı fonksiyon
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
        motor.motor0degree = message.message.substring(commaIndex[15*i+1]+1,commaIndex[15*i+2]).toInt();
        motor.motor1degree = message.message.substring(commaIndex[15*i+2]+1,commaIndex[15*i+3]).toInt();
        motor.motor2degree = message.message.substring(commaIndex[15*i+3]+1,commaIndex[15*i+4]).toInt();
        motor.motor3degree = message.message.substring(commaIndex[15*i+4]+1,commaIndex[15*i+5]).toInt();
        motor.motor4degree = message.message.substring(commaIndex[15*i+5]+1,commaIndex[15*i+6]).toInt();
        int motor0hiz = message.message.substring(commaIndex[15*i+6]+1,commaIndex[15*i+7]).toInt();
        int motor1hiz = message.message.substring(commaIndex[15*i+7]+1,commaIndex[15*i+8]).toInt();
        int motor2hiz = message.message.substring(commaIndex[15*i+8]+1,commaIndex[15*i+9]).toInt();
        int motor3hiz = message.message.substring(commaIndex[15*i+9]+1,commaIndex[15*i+10]).toInt();
        int motor4hiz = message.message.substring(commaIndex[15*i+10]+1,commaIndex[15*i+11]).toInt();
        int motor0ivme = message.message.substring(commaIndex[15*i+11]+1,commaIndex[15*i+12]).toInt();
        int motor1ivme = message.message.substring(commaIndex[15*i+12]+1,commaIndex[15*i+13]).toInt();
        int motor2ivme = message.message.substring(commaIndex[15*i+13]+1,commaIndex[15*i+14]).toInt();
        int motor3ivme = message.message.substring(commaIndex[15*i+14]+1,commaIndex[15*i+15]).toInt();
        int motor4ivme = message.message.substring(commaIndex[15*i+15]+1,commaIndex[15*i+16]).toInt();
        setAccelandSpeed(0, motor0ivme, motor0hiz);
        setAccelandSpeed(1, motor1ivme, motor1hiz);
        setAccelandSpeed(2, motor2ivme, motor2hiz);
        setAccelandSpeed(3, motor3ivme, motor3hiz);
        setAccelandSpeed(4, motor4ivme, motor4hiz);

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



