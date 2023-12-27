#ifndef MACSTEPPER_H
#define MACSTEPPER_H

#include <Arduino.h>

#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62

#define E0_STEP_PIN 26
#define E0_DIR_PIN 28
#define E0_ENABLE_PIN 24

#define E1_STEP_PIN 36
#define E1_DIR_PIN 34
#define E1_ENABLE_PIN 30

#define B1_STEP_PIN 32
#define B1_DIR_PIN 47

#define B2_STEP_PIN 45
#define B2_DIR_PIN 43

#define X_STEP_HIGH             PORTF |=  0b00000001;
#define X_STEP_LOW              PORTF &= ~0b00000001;

#define Y_STEP_HIGH             PORTF |=  0b01000000;
#define Y_STEP_LOW              PORTF &= ~0b01000000;

#define Z_STEP_HIGH             PORTL |=  0b00001000;
#define Z_STEP_LOW              PORTL &= ~0b00001000;

#define E0_STEP_HIGH             PORTA |=  0b00010000;  //e0
#define E0_STEP_LOW              PORTA &= ~0b00010000;

#define E1_STEP_HIGH             PORTC |=  0b00000010;  //e1
#define E1_STEP_LOW              PORTC &= ~0b00000010;

#define B1_STEP_HIGH             PORTC |=  0b00100000;  //b1
#define B1_STEP_LOW              PORTC &= ~0b00100000;

#define B2_STEP_HIGH             PORTL |=  0b00010000;  //b2
#define B2_STEP_LOW              PORTL &= ~0b00010000;

#define TIMER1_INTERRUPTS_ON    TIMSK1 |=  (1 << OCIE1A);
#define TIMER1_INTERRUPTS_OFF   TIMSK1 &= ~(1 << OCIE1A);

struct stepperInfo {
  // externally defined parameters
  float acceleration;
  volatile unsigned long minStepInterval; // ie. max speed, smaller is faster
  void (*dirFunc)(int);
  void (*stepFunc)();
  float stepPerDegree;

  // derived parameters
  unsigned int c0;                // step interval for first step, determines acceleration
  long stepPosition;              // current position of stepper (total of all movements taken so far)

  // per movement variables (only changed once per movement)
  volatile int dir;                        // current direction of movement, used to keep track of position
  volatile unsigned int totalSteps;        // number of steps requested for current movement
  volatile bool movementDone = false;      // true if the current movement has been completed (used by main program to wait for completion)
  volatile unsigned int rampUpStepCount;   // number of steps taken to reach either max speed, or half-way to the goal (will be zero until this number is known)
  volatile unsigned long estStepsToSpeed;  // estimated steps required to reach max speed
  volatile unsigned long estTimeForMove;   // estimated time (interrupt ticks) required to complete movement
  volatile unsigned long rampUpStepTime;
  volatile float speedScale;               // used to slow down this motor to make coordinated movement with other motors

  // per iteration variables (potentially changed every interrupt)
  volatile unsigned int n;                 // index in acceleration curve, used to calculate next interval
  volatile float d;                        // current interval length
  volatile unsigned long di;               // above variable truncated
  volatile unsigned int stepCount;         // number of steps completed in current movement
};
void xStep();
void xDir(int dir);

void yStep();
void yDir(int dir);

void zStep();
void zDir(int dir);

void e0Step();
void e0Dir(int dir);

void e1Step();
void e1Dir(int dir);

void b1Step();
void b1Dir(int dir);

void b2Step();
void b2Dir(int dir);

void b12Step();
void b12Dir(int dir);

void resetStepperInfo( stepperInfo& si );
void resetStepper(volatile stepperInfo& si);

float getDurationOfAcceleration(volatile stepperInfo& s, unsigned int numSteps);
void prepareMovement(int whichMotor, int degrees);
void setNextInterruptInterval();

void adjustSpeedScales();
void runAndWait();
void initSettings();
void sendInfo(void);
#endif // MACSTEPPER_H
