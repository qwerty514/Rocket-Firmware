#include <BMI160.h>
#include <CurieIMU.h>

#define Cereal Serial

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  Cereal.begin(9600);
  CurieIMU.begin();
  CurieIMU.setAccelerometerRate(1600);
  CurieIMU.setAccelerometerRange(2);
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  float ax, ay, az;
  float angley, anglez;
  CurieIMU.readAccelerometerScaled(ax, ay, az);
  
  angley = ax * ax + ay * ay;
  angley = sqrt(angley);
  angley = az/angley;
  angley = tan(angley);
  angley = angley * -57.2957795;
  
  anglez = ay * ay + az * az;
  anglez = sqrt(anglez);
  anglez = ax/anglez;
  anglez = tan(anglez);
  anglez = anglez * 57.2957795;
  Cereal.println(anglez);
  delay(20);
}
