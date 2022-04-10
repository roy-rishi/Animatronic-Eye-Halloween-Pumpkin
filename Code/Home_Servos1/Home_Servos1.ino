/* This program will home (set to 90 deg) servos that are connected to any
 *  digital pin on an Arduino Nano.
 */


#include <Servo.h>

Servo servo[12]; // creates 12 servo objects
byte servoPins[0]; // array for servo pins


void setup() {

  for (byte i = 0; i <= 11; i++) { // fills "servoPins" with pins 2-13
    servoPins[i] = i + 2;
  }

  for (byte i = 0; i <= 11; i++) { // attaches servos to pins D2-D13
    servo[i].attach(servoPins[i]);
  }

  for (byte i = 0; i <= 11; i++) { // commands all servos to go to 90º
    servo[i].write(90);
  }
}

void loop() {
}
