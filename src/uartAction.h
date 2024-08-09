#ifndef UART_ACTION_H
#define UART_ACTION_H
#include "uart.h"

void moveMotor(motorSettings& motor);
void goMotor(motorSettings& motor);
void setCurrentDegree(motorSettings& motor);
void setCurrentDegreeGo(motorSettings& motor);
void offsetMotor(motorSettings& motor);
void hizivmeAyarla(motorSettings& motor , messageProtocol& message);
void missionMotor(motorSettings& motor, messageProtocol& message);
void missionMotorWithAccel(motorSettings& motor, messageProtocol& message);
void mehter(motorSettings& motor);
void sagHareket(motorSettings& motor);
void solHareket(motorSettings& motor);

#endif // UART_ACTION_H
