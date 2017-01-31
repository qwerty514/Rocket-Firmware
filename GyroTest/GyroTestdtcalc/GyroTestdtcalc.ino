#include <BMI160.h>
#include <CurieIMU.h>

#define Cereal Serial

double dt, tlast, tnow;
double anglex=0, angley=0, anglez=0;

void setup() {
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Cereal.begin(9600);
  CurieIMU.begin();
  CurieIMU.setGyroRate(1600);
  CurieIMU.setGyroRange(500);
  delay(10);
  CurieIMU.autoCalibrateGyroOffset();
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  tlast=(tnow=micros());
}

void loop() {
  float gx, gy, gz;
  
  dt=(tnow-tlast)/1000000;
  tlast=tnow;
  tnow=micros();
  
  CurieIMU.readGyroScaled(gx, gy, gz);
  anglex = anglex + gx * dt;
  angley = angley + gy * dt;
  anglez = anglez + gz * dt;
  
  Cereal.print(anglex);
  Cereal.print("\t");
  Cereal.print(angley);
  Cereal.print("\t");
  Cereal.print(anglez);
  Cereal.print("\t");
  Cereal.print(dt);
  Cereal.println();
}
