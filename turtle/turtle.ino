#include <Servo.h> 
 
int servo1Pin = 9;
int servo2Pin = 10;
 
Servo s1;  
Servo s2;  
 
void setup() 
{ 
  s1.attach(servo1Pin); 
  s2.attach(servo2Pin); 
  right(180);
  delay(1000);
  left(180);
} 
 
void servoFw(Servo s) {
  s.writeMicroseconds(1600);
}

void servoBk(Servo s) {
  s.writeMicroseconds(1400);
}

void servoStop(Servo s) {
  s.writeMicroseconds(1500);
}

void servosStop() {
  servoStop(s1);
  servoStop(s2); 
}

void forward(int units) {
  servoBk(s1);
  servoFw(s2);
  delay(units*1000);
  servosStop();
}

void backward(int units) {
  servoFw(s1);
  servoBk(s2);
  delay(units*1000);
  servosStop();
}

int angleToTimeRight(int units) {
  if (units <= 90) {
    return 7.2*units;
  } if (units <= 180) {
    return 6.8*units;
  } else {
    return 6.4*units; 
  }
}

int angleToTimeLeft(int units) {
  if (units <= 90) {
    return 6.4*units;
  } if (units <= 180) {
    return 6.1*units;
  } else {
    return 5.6*units; 
  }
}

void right(int units) {
  servoFw(s1);
  servoFw(s2);
  delay(angleToTimeRight(units));
  servosStop();
}

void left(int units) {
  servoBk(s1);
  servoBk(s2);
  delay(angleToTimeLeft(units));
  servosStop();
}
 
void loop() 
{ 
//  forward(1);
//  delay(1000);
//  backward(1);
//  delay(1000);
} 
