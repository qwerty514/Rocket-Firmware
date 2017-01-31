#include <BMI160.h>
#include <CurieIMU.h>
#include <CurieTimerOne.h>


#define SECOND 1000000
#define TICKRATE 400
#define INTERRUPTTIME (SECOND/TICKRATE)
#define Cereal Serial

double anglex=0, angley=0, anglez=0;

void CalcAngle(){
  float gx, gy, gz;
  CurieIMU.readGyroScaled(gx, gy, gz);
  anglex = anglex + gx / TICKRATE;
  angley = angley + gy / TICKRATE;
  anglez = anglez + gz / TICKRATE;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  Cereal.begin(250000);
  CurieIMU.begin();
  CurieIMU.setGyroRate(TICKRATE);
  CurieIMU.setGyroRange(250);
  CurieIMU.autoCalibrateGyroOffset();
  delay(50);
  CurieIMU.autoCalibrateGyroOffset();
  delay(50);
  CurieIMU.attachInterrupt(&CalcAngle);
  CurieIMU.interrupts(CURIE_IMU_DATA_READY);
  //CurieTimerOne.start(INTERRUPTTIME, &CalcAngle);

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  Cereal.print(anglex);
  Cereal.print("\t");
  Cereal.print(angley);
  Cereal.print("\t");
  Cereal.print(anglez);
  Cereal.println();
  delay(50);
}
