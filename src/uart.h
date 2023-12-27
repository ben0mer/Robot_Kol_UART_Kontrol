#ifndef UART_H
#define UART_H
#include <Arduino.h>

struct messageProtocol
{
    const char startChar = '<';
    const char endChar = '>';
    const char separatorChar = ',';
    String message = "";
    bool messageComplete = false;
    bool dataFlow = false;
};

struct motorSettings
{
    int motor0currentDegree;
    int motor1currentDegree;
    int motor2currentDegree;
    int motor3currentDegree;
    int motor4currentDegree;
    int motor0degree;
    int motor1degree;
    int motor2degree;
    int motor3degree;
    int motor4degree;
};



void messageReset(void);
void serialEvent(void);
void messageParser(void);
void uartInit(void);

#endif // UART_H
