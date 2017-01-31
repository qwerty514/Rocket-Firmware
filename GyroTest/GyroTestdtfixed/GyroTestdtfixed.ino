#include <BMI160.h>
#include <CurieIMU.h>

#define TICKRATE 1600
#define Cereal Serial

unsigned long tlast;
double anglex=0, angley=0, anglez=0;
const unsigned long dt = 1000000 / TICKRATE;

void setup() {
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Cereal.begin(250000);
  CurieIMU.begin();
  CurieIMU.setGyroRate(TICKRATE);
  CurieIMU.setGyroRange(500);
  CurieIMU.autoCalibrateGyroOffset();
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  
  tlast = micros();
}

void loop() {
  float gx, gy, gz;
  
  if(micros() - tlast >= dt) {
    tlast = tlast + dt;
    CurieIMU.readGyroScaled(gx, gy, gz);
    anglex = anglex + gx / TICKRATE;
    angley = angley + gy / TICKRATE;
    anglez = anglez + gz / TICKRATE;
    Cereal.print(anglex);
    Cereal.print("\t");
    Cereal.print(angley);
    Cereal.print("\t");
    Cereal.print(anglez);
    Cereal.println();
  }
}
