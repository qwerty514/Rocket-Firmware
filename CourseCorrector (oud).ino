#include <BMI160.h>
#include <CurieIMU.h>
#include <Servo.h>

#define Cereal Serial

//Gyro globals
double dt, tlast, tnow;
double anglex = 0, angley = 0, anglez = 0;

//Servo globals
const servopin[4] = {3,5,6,9};
Servo wingservo[4];
int servopos[4] = {90,90,90,90};

void setup() {
  delay(500);
  
  //Blink LED to show init process
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  
  //Gyro init
  CurieIMU.begin();
  CurieIMU.setGyroRate(1600);
  CurieIMU.setGyroRange(500);
  delay(10);
  CurieIMU.autoCalibrateGyroOffset();

  //Servo Init
  for(int i = 0; i < 4; i++){
    wingservo[i].attach(servopin[i]);
    wingservo[i].write(servopos[i]);
  }

  //Time init
  dt = 0;
  
  //Turn LED on to show init finished
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  //Gyro
  static float gx, gy, gz;
  anglex = anglex + gx * dt;
  angley = angley + gy * dt;
  anglez = anglez + gz * dt;
  CurieIMU.readGyroScaled(gx, gy, gz);
  tlast = tnow;
  tnow = micros();
  dt = (tnow - tlast) / 1000000;

  //Course correction
  
  
  //Servo
  for(int i = 0; i < 4; i++) wingservo[i].write(servopos[i]);
}
