#include <Servo.h>

Servo myservo;          // create servo object to control a servo

#define enable_run 5
#define m1_a 3
#define m1_b 4

#define enable_turn 9
#define m2_a 10
#define m2_b 11

void setup() {

  myservo.attach(1);    // attaches the servo on pin 9 to the servo object
  myservo.write(90);    // STOP
  
  pinMode(enable_run,OUTPUT);
  pinMode(m1_a,OUTPUT);
  pinMode(m1_b,OUTPUT);

  pinMode(enable_turn,OUTPUT);
  pinMode(m2_a,OUTPUT);
  pinMode(m2_b,OUTPUT);

  //Serial.begin(9600);
  enableMotors();
}

void loop() {
  
  
  watchRightAndReturn();
  watchLeftAndReturn();
  delay(2000);

  //turnRight();
  //turnLeft();
  
  goAhead();
  goBack();   

  //disableMotors();
  delay(2000);  
}

void enableMotors(){
  analogWrite(enable_run,128);      // full speed
  digitalWrite(enable_turn,HIGH);   // full speed
}

void disableMotors(){  
  digitalWrite(enable_run,LOW);   // disable
  digitalWrite(enable_turn,LOW);  // enable on
}

void turnLeft(){
  Serial.println("Turning one side");  
  digitalWrite(m2_a,HIGH);
  digitalWrite(m2_b,LOW);
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,LOW);
  delay(1000);
  digitalWrite(m2_a,LOW);
  digitalWrite(m2_b,LOW);
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,LOW);
}

void turnRight(){
  Serial.println("Turning other side");
  digitalWrite(m2_a,LOW);
  digitalWrite(m2_b,HIGH);
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,LOW);
  delay(1000);
  digitalWrite(m2_a,LOW);
  digitalWrite(m2_b,LOW);
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,LOW);
}

void goAhead(){
  Serial.println("Running ahead");
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,HIGH);
  digitalWrite(m2_a,LOW);
  digitalWrite(m2_b,LOW);    
  delay(2000);
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,LOW);
  digitalWrite(m2_a,LOW);
  digitalWrite(m2_b,LOW);
}

void goBack(){
  Serial.println("Reverse");
  digitalWrite(m1_a,HIGH);
  digitalWrite(m1_b,LOW);
  digitalWrite(m2_a,LOW);
  digitalWrite(m2_b,LOW);
  delay(2000);
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,LOW);
  digitalWrite(m2_a,LOW);
  digitalWrite(m2_b,LOW);
}

void watchRightAndReturn(){
  myservo.write(0);       // MOVE HEAD CLOCKWISE
  delay(250); 
  myservo.write(180);     // MOVE HEAD COUNTER-CLOCKWISE
  delay(250); 
  myservo.write(90);      // STOP
}

void watchLeftAndReturn(){
  myservo.write(180);     // MOVE HEAD COUNTER-CLOCKWISE
  delay(250); 
  myservo.write(0);       // MOVE HEAD CLOCKWISE
  delay(250); 
  myservo.write(90);      // STOP 
}

