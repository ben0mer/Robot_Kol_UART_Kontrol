#ifndef UART_ACTION_H
#define UART_ACTION_H
#include "uart.h"

void moveMotor(motorSettings& motor);
void goMotor(motorSettings& motor);
void setCurrentDegree(motorSettings& motor);
void setCurrentDegreeGo(motorSettings& motor);
void offsetMotor(motorSettings& motor);
void missionMotor(motorSettings& motor, messageProtocol& message);


#endif // UART_ACTION_H
