#include <BMI160.h>
#include <CurieIMU.h>
#include <Servo.h>

#define Cereal Serial

//Gyro globals
double dt, tlast, tnow;
double anglex = 0, angley = 0, anglez = 0;

Servo wingservo[4];
int servopos[4];
//Servo globals
const char servopin[4] = {3,5,6,9};
int stdservopos[4] = {62, 80, 78, 90};

void setup() {
  delay(500);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  
  //Gyro init
  Cereal.begin(115200);
  CurieIMU.begin();
  CurieIMU.setGyroRate(50);
  CurieIMU.setGyroRange(500);
  delay(10);
  CurieIMU.autoCalibrateGyroOffset();

  //Servo Init
  for(int i = 0; i < 4; i++){
    servopos[i] = stdservopos[i];
    wingservo[i].attach(servopin[i]);
    wingservo[i].write(servopos[i]);
  }

  //Time init
  dt = 0;
  
  //Turn LED on to show init finished
  digitalWrite(LED_BUILTIN, HIGH);
}

int prison(int input, int wall){
  if(input > wall) input = wall;
  if(input < -wall) input = wall;
  return input;
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
  ///*
  Cereal.print(anglex);
  Cereal.print("\t");
  Cereal.print(angley);
  Cereal.print("\t");
  Cereal.print(anglez);
  Cereal.print("\t");
  Cereal.println(dt);
  //*/
  
  /*
   * Als raket naar kant van 4 buigt, waarde y positief
   *  - 1 negatief
   *  - 3 positief
   * Als raket naar kant van 2 buitgt, waarde y negatief
   *  - 1 positief
   *  - 3 negatief
   * Als waarde naar kant van 3 buigt, waarde z negatief
   *  - 2 positief
   *  - 4 negatief
   * Als waarde naar kant 1 buigt, waarde z positief
   *  - 2 negatief
   *  - 4 positief
   * Als clockwise van onder x is positief
   * Als counter clockwise van onder x is negatief
   */
  
  //Course correction
  int minimum, maximum;
  servopos[0] = stdservopos[0] - angley + 0.5 * anglex;
  servopos[2] = stdservopos[2] + angley + 0.5 * anglex;
  servopos[1] = stdservopos[1] - anglez + 0.5 * anglex;
  servopos[3] = stdservopos[3] + anglez + 0.5 * anglex;
  for(int i = 0; i < 4; i++){
    maximum = stdservopos[i] + 45;
    if(servopos[i] > maximum) servopos[i] = maximum;
    else{
      minimum = stdservopos[i] - 45;
      if(servopos[i] < minimum) servopos[i] = minimum;
    }
  }
  
  //Servo control
  for(int i = 0; i < 4; i++) wingservo[i].write(servopos[i]);
}
