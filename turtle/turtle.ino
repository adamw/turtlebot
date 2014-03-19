#include <Servo.h> 
 
int servo1Pin = 9;
int servo2Pin = 10;
int penPin = 11;
boolean isPenUp = true;
boolean compensate = true;
 
Servo s1;  
Servo s2;  
Servo pen;
 
void setup() 
{ 
  s1.attach(servo1Pin); 
  s2.attach(servo2Pin); 
  pen.attach(penPin);

  penDown();

//penDown();  
//  penUp();
  
//  right(90);
//  delay(1000);
//  left(90);

forward(10);
right(90);
forward(10);
//delay(1000);
//backward(10);
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
  delay(units*100);
  servosStop();
  
  delay(500);
}

void backward(int units) {
  servoFw(s1);
  servoBk(s2);
  delay(units*100);
  servosStop();
  
  delay(500);
}

int angleToTimeRight(int units) {
  if (units <= 90) {
    return 6.8*units;
  } if (units <= 180) {
    return 6.4*units;
  } else {
    return 6.2*units; 
  }
}

int angleToTimeLeft(int units) {
  if (units <= 90) {
    return 6.4*units;
  } if (units <= 180) {
    return 6.0*units;
  } else {
    return 6.0*units; 
  }
}

void right(int units) {
  boolean wasPenUp = isPenUp;
  
  if (compensate) {
    penUp();
    forward(5);
  }
  
  servoFw(s1);
  servoFw(s2);
  delay(angleToTimeRight(units));
  servosStop();
  delay(500);
  
  if (compensate) {
    backward(5);
    if (!wasPenUp) {
       penDown(); 
    } 
  }
}

void left(int units) {
  boolean wasPenUp = isPenUp;
  
  if (compensate) {
    penUp();
    forward(7);
  }
  
  servoBk(s1);
  servoBk(s2);
  delay(angleToTimeLeft(units));
  servosStop();
  delay(500);
  
  if (compensate) {
    backward(7);
    if (!wasPenUp) {
       penDown(); 
    } 
  }
}

void penUp() {
  pen.write(0);
  isPenUp = true;
  delay(500);
}

void penDown() {
  pen.write(90);  
  isPenUp = false;
  delay(500);
}
 
void loop() 
{ 
//  forward(1);
//  delay(1000);
//  backward(1);
//  delay(1000);
} 
