// Servo motor

#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(D5); // Use the GPIO pin you connected the signal to
}

void loop() {
  myServo.write(0);    // Full speed in one direction
  delay(2000);
  myServo.write(90);   // Stop
  delay(1000);
  myServo.write(180);  // Full speed in the other direction
  delay(2000);
  myServo.write(90);   // Stop
  delay(1000);
}

