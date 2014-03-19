//#define ON_SPARK 1

#ifndef ON_SPARK
#include <Servo.h> 
#endif

int servo1Pin = 9;
int servo2Pin = 10;
int penPin = 11;
boolean isPenUp = true;
boolean compensate = false;

Servo s1;  
Servo s2;  
Servo pen;

void setup() 
{ 
  s1.attach(servo1Pin); 
  s2.attach(servo2Pin); 
  pen.attach(penPin);

#ifdef ON_SPARK
  Spark.function("forward", cmdForward);
  Spark.function("backward", cmdBackward);
  Spark.function("right", cmdRight);
  Spark.function("left", cmdLeft);
  Spark.function("up", cmdPenUp);
  Spark.function("down", cmdPenDown);
#endif

  penUp();
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
  } 
  if (units <= 180) {
    return 6.4*units;
  } 
  else {
    return 6.2*units; 
  }
}

int angleToTimeLeft(int units) {
  if (units <= 90) {
    return 6.4*units;
  } 
  if (units <= 180) {
    return 6.0*units;
  } 
  else {
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
    forward(5);
  }

  servoBk(s1);
  servoBk(s2);
  delay(angleToTimeLeft(units));
  servosStop();
  delay(500);

  if (compensate) {
    backward(5);
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

#ifdef ON_SPARK
int cmdForward(String param) {
  int units = param.toInt();
  if (units != 0) {
    forward(units);
  }
  return 1;
}

int cmdBackward(String param) {
  int units = param.toInt();
  if (units != 0) {
    backward(units);
  }
  return 1;
}

int cmdRight(String param) {
  int units = param.toInt();
  if (units != 0) {
    right(units);
  }
  return 1;
}

int cmdLeft(String param) {
  int units = param.toInt();
  if (units != 0) {
    left(units);
  }
  return 1;
}

int cmdPenUp(String param) {
  penUp();
  return 1;
}

int cmdPenDown(String param) {
  penDown();
  return 1;
}
#endif

