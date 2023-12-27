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
}

void goMotor(motorSettings& motor){
    if((motor.motor0degree - motor.motor0currentDegree) != 0){
        prepareMovement(0, motor.motor0degree-motor.motor0currentDegree);
    }
    if((motor.motor1degree - motor.motor1currentDegree) != 0){
        prepareMovement(1, motor.motor1degree-motor.motor1currentDegree);
    }
    if((motor.motor2degree - motor.motor2currentDegree) != 0){
        prepareMovement(2, motor.motor2degree-motor.motor2currentDegree);
    }
    if((motor.motor3degree - motor.motor3currentDegree) != 0){
        prepareMovement(3, motor.motor3degree-motor.motor3currentDegree);
    }
    if((motor.motor4degree - motor.motor4currentDegree) != 0){
        prepareMovement(4, motor.motor4degree-motor.motor4currentDegree);
    }
    setCurrentDegree(motor);
    runAndWait();
}



