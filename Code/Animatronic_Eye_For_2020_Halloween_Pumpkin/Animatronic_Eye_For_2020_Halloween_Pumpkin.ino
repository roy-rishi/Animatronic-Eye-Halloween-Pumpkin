/* This is the code to control the Halloween pumpkin with an animatronic eye.
   Author: Zero To Infinity
   The Instructable with instructions is here:
   https://www.instructables.com/A-Halloween-Pumpkin-With-a-Moving-Animatronic-Eye-/

   When the Ultrasonic sensor is triggered, the eye will either move in a jittery fashion, or roll
   its eye. Although there is only one version of code, the Ultrasonic sensor remains optional because
   if no Ultrasonic sensor is plugged into the Arduino the loop function will automatically execute.

   You can choose if the pumpkin's eye moves in a jittery fashion or rolls at line 38.
*/

#include <Servo.h>

Servo hServo; // creates horizontal servo
Servo vServo; // creates vertical servo

int randomH; // define random horizontal position variable
int randomV; // define random vertical position variable
int randomDelay; //define random movement delay variable
int Repeats = 40; // define the number of eye movements to do before waiting for another sonar ping

const byte hLeftLIMIT = 55; // define left limit of horizontal servo
const byte hRightLIMIT = 110; // define right limit of horizontal servo
const byte vTopLIMIT = 60; // define bottom limit of vertical servo
const byte vBotLIMIT = 155; // define top limit of vertical servo
const int hServoCenterTrim = -1; // adjust this value to precisely center the horizontal servo
const int vServoCenterTrim = -13; // adjust this value to precisely center the horizontal servo

const byte hServoPin = 8; // define the pin to connect the horizontal servo to
const byte vServoPin = 9; // define the pin to connect the vertical servo to
const byte ultrasonic1[] = {3, 2}; // defines trig and echo pins, respectively

float duration;
long distance;
const long triggerDistance = 1000; // set the max distance (mm) before the ultrasonic sensor is triggered

const byte whatFunctionToCall = 1; // (0-1) tells the program which function to call
// rollEyes = 0
// randomTwitching = 1

void setup() {
  pinMode(ultrasonic1[0], OUTPUT); // sets trig pin as output
  pinMode(ultrasonic1[1], INPUT); // sets echo pin as input
  digitalWrite(ultrasonic1[0], LOW);

  hServo.attach(hServoPin); // assigns horizontal servo to a digital pin
  vServo.attach(vServoPin); // assigns vertical servo to a digital pin
  hServo.write((hRightLIMIT + hLeftLIMIT) / 2 + hServoCenterTrim); // centers horizontal servo
  vServo.write((vBotLIMIT + vTopLIMIT) / 2 + vServoCenterTrim); // centers horizontal servo

  randomSeed(analogRead(0)); /* creates some random values using analog noise from a floating
  analog pin */
  Serial.begin(9600);
}

void loop() {
  distance = distanceRead(3, 2);
  while (distance > triggerDistance) {
    delayMicroseconds(2);
    distance = distanceRead(3, 2);
  }

  if (whatFunctionToCall == 0) {
    for (int b = 0; b <= Repeats; b++) {
      rollEye();
    }
  }

  if (whatFunctionToCall == 1) {
    for (int b = 0; b <= Repeats; b++) {
      randomTwitching();
    }
  }

  hServo.write((hRightLIMIT + hLeftLIMIT) / 2 + hServoCenterTrim); // centers horizontal servo
  vServo.write((vBotLIMIT + vTopLIMIT) / 2 + vServoCenterTrim); // centers horizontal servo
}



float distanceRead(int trigPin, int echoPin) {

  digitalWrite(trigPin, HIGH); // Tell sensor to start a distance read
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float result = duration * 0.343 / 2; // returns value in mm/μs
  return result;
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float parabola(float a) {
  float result;
  result = -4 * sq(a - 0.5) + 1;
  return result;
}

void rollEye() {
  // Rolls Eye One Time
  for (float i = 0; i <= 1; i = i + 0.05) {
    float x = i;
    float y = parabola(x);

    x = floatMap(x, 0, 1, hLeftLIMIT, hRightLIMIT);
    y = floatMap(y, 0, 1, vBotLIMIT, vTopLIMIT);

    hServo.write(x);
    vServo.write(y);

    delay(30);
  }
  for (float i = 1; i >= 0; i = i - 0.05) {
    float x = i;

    x = floatMap(x, 0, 1, hLeftLIMIT, hRightLIMIT);

    hServo.write(x);
    vServo.write(vBotLIMIT);

    delay(25);
  }
  delay(200);
}

void randomTwitching() {
  randomH = random(hLeftLIMIT, hRightLIMIT); // random x position for horizontal servo
  randomV = random(vTopLIMIT, vBotLIMIT); // random y position for vertical servo
  randomDelay = random(30, 850); // random delay between eye movements

  hServo.write(randomH); // commands horizontal servo
  vServo.write(randomV); // commands vertical servo
  delay(randomDelay);
}
