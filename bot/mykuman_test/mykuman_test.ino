#include <Servo.h>
#include <Chrono.h>

int ENA = 5;
int ENB = 6;
int INPUT1 = 8;
int INPUT2 = 7;
int INPUT3 = 12;
int INPUT4 = 13;

int Echo = A5;
int Trig = A4;
float distance;
float lDistance;
float rDistance;

Servo servo1;
Servo servo2;
byte hAngle=90;
byte vAngle=0;
int pos = 0;    // variable to store the servo position

#define MOTOR_GO_FORWARD   {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}
#define MOTOR_GO_BACK  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}
#define MOTOR_GO_LEFT    {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}
#define MOTOR_GO_RIGHT   {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}
#define MOTOR_GO_STOP   {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,LOW);}
#define HEAD_LEFT {for(hAngle;hAngle<=180;hAngle++){servo1.write(hAngle);delay(15);}}
#define HEAD_RIGHT {for(hAngle;hAngle>=0;hAngle--){servo1.write(hAngle);delay(15);}}
#define HEAD_CENTER {servo1.write(90);delay(500);hAngle=90;}

// Instantiate two Chronos
Chrono chronoMoveHead;
Chrono chronoGetDistance; 
Chrono chronoMove; 

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(ENA,OUTPUT); 
  pinMode(ENB,OUTPUT); 
  pinMode(INPUT1,OUTPUT); 
  pinMode(INPUT2,OUTPUT); 
  pinMode(INPUT3,OUTPUT); 
  pinMode(INPUT4,OUTPUT);
  analogWrite(ENB,128);
  analogWrite(ENA,128);

  pinMode(Echo,INPUT);
  pinMode(Trig,OUTPUT);

  servo1.attach(9);
  servo1.write(hAngle);
  servo2.attach(10);
  servo2.write(vAngle);
  headLeft();
  delay(500);
  HEAD_CENTER;
  headRight();
  delay(500);
  HEAD_CENTER;
  headUp();
  delay(1000);
  headStraight();

  // READING DISTANCE A FEW TIMES TO GET LATER MORE ACCURATE MEASUREMENTS
  getDistance();
  getDistance();
  getDistance();
  getDistance();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  getDistance();  
  
  if ( distance <= 25 ) {
    MOTOR_GO_STOP;
    delay(100);
    MOTOR_GO_BACK;
    delay(400);
    MOTOR_GO_STOP;
    headLeft();
    headRight();
    HEAD_CENTER;
    getDistance();
    if ( lDistance >= rDistance && lDistance > distance) {
      MOTOR_GO_LEFT;
      delay(400);
      MOTOR_GO_STOP;
    } else if ( rDistance >= lDistance && rDistance > distance) {
      MOTOR_GO_RIGHT;
      delay(400);
      MOTOR_GO_STOP;
    } else {
      MOTOR_GO_FORWARD;
    }
  } else {
    MOTOR_GO_FORWARD;
  }  
  
}

void headLeft() {
  for (pos = hAngle; pos <= 180; pos ++) { 
    servo1.write(pos);              // tell servo to go to position in variable 'pos'    
    hAngle = pos;   
    if ( pos == 180 ) {
      lDistance = getDistance();
      delay(200);      
    } else {
      delay(3);
    }
  }
}

void headRight() {
  for (pos = hAngle; pos >= 0; pos --) { 
    servo1.write(pos);              // tell servo to go to position in variable 'pos'    
    hAngle = pos;
    if ( pos == 0 ) {
      rDistance = getDistance();
      delay(200);
    } else {
      delay(3);
    }
  }
}

void headUp() {
  for (pos = vAngle; pos <= 65; pos ++) {
    servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 5ms for the servo to reach the position
    vAngle = pos;
  }
}

void headDown() {
  for (pos = vAngle; pos >= 0; pos --) {
    servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 5ms for the servo to reach the position
    vAngle = pos;
  }
}

void headStraight() {
  servo2.write(0);
  vAngle = 0;
}

char getDistance() {  
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);  
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);  
    digitalWrite(Trig, LOW);
    distance = pulseIn(Echo, HIGH);
    distance = distance/5.8/10;
    return distance;    
}
