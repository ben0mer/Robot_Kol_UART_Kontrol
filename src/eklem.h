#include <main.cpp>
struct Eklem {
  int stepPin;
  int dirPin;
  int stepPin2; // İkinci motor için
  int dirPin2;  // İkinci motor için
  float cozunurluk;

  Eklem(int step, int dir, float coz) {
    stepPin = step;
    dirPin = dir;
    stepPin2 = B2_STEP_PIN; // İkinci motor için pin numaraları
    dirPin2 = B2_DIR_PIN;
    cozunurluk = coz/90.0; // 90 derece için çözünürlük degeri girilmesi gerekiyor.
  }

  // İkinci motoru etkinleştirmek için bir işlev
  void ikinciMotor(int step, int dir) {
    stepPin2 = step;
    dirPin2 = dir;
  }
};
