#include <Servo.h>

Servo testservo;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  testservo.attach();
  testservo.write(90);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  //put your main code here, to run repeatedly
  delay(1000);
  testservo.write(0);
  delay(1000);
  testservo.write(90);
  delay(1000);
  testservo.write(180);

}
