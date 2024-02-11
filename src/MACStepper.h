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
  // Dışarıdan Tanımlanacak Parametreler
  float acceleration;                      // İvme
  volatile unsigned long minStepInterval;  // Maksimum hız, ne kadar küçükse o kadar hızlıdır.
  void (*dirFunc)(int);                    // Yön Fonksiyonu
  void (*stepFunc)();                      // Adım Fonksiyonu
  float stepPerDegree;                     // Derece başına adım sayısı

   // Türetilmiş Parametreler
  unsigned int c0;                         // İlk adım için adım aralığı, hızlanmayı belirler
  long stepPosition;                       // Step motorun şuanki konumu (Şuana kadar gerçekleştirilmiş hareketlerin toplamı)

  // Hareket Parametreleri (Hareket başında yalnızca bir defa değiştirilir.)
  volatile int dir;                        // Konumu takip etmek için kullanılacak mevcut hareket yönü
  volatile unsigned int totalSteps;        // Mevcut hareket için istenen toplam adım sayısı
  volatile bool movementDone = false;      // Hareket tamamlanmış ise "true" değerini alır. Main program tarafından hareketin tamamlandığını kontrol etmek için kullanılır.
  volatile unsigned int rampUpStepCount;   // Maksimum hıza veya hedefin yarısına ulaşmak için atılan adım sayısı. Bu sayı bilinene kadar sıfır olacaktır.
  volatile unsigned long estStepsToSpeed;  // Maksimum hıza ulaşmak için gerekli tahmini adım sayısı.
  volatile unsigned long estTimeForMove;   // Hareketi tamamlamak için gerekli tahmini süre (Timer İnterrupt Tick)
  volatile unsigned long rampUpStepTime;   // Maksimum hıza ulaşmak için gereken tahmini süre (Timer İnterrupt Tick)
  volatile float speedScale;               // Diğer motorlarla koordineli hareket yapmak amacıyla bu motoru yavaşlatmak  için bu katsayı kullanılır.

  // İterasyon Parametreleri (Her kesmede değişebilir)
  volatile unsigned int n;                 // Bir sonraki aralığı hesaplamak için kullanılan hızlanma eğrisindeki indeks
  volatile float d;                        // Mevcut aralık uzunluğu
  volatile unsigned long di;               // Yukarıdaki değişken kesildi
  volatile unsigned int stepCount;         // Mevcut harekette tamamlanan step sayısı
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
