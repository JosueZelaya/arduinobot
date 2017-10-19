#define enable_run 5
#define m1_a 3
#define m1_b 4

#define enable_turn 9
#define m2_a 10
#define m2_b 11

void setup() {
  pinMode(enable_run,OUTPUT);
  pinMode(m1_a,OUTPUT);
  pinMode(m1_b,OUTPUT);

  pinMode(enable_turn,OUTPUT);
  pinMode(m2_a,OUTPUT);
  pinMode(m2_b,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  digitalWrite(enable_run,HIGH);
  digitalWrite(enable_turn,HIGH);

  Serial.println("Turning one side");  
  digitalWrite(m2_a,HIGH); //one way
  digitalWrite(m2_b,LOW);
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,LOW);
  delay(2000);
  Serial.println("Turning other side");
  digitalWrite(m2_a,LOW);  //reverse
  digitalWrite(m2_b,HIGH);
  digitalWrite(m1_a,LOW);
  digitalWrite(m1_b,LOW);
  delay(2000);
  
  //---back and forth example  
  for (int i=0;i<2;i++) {
    Serial.println("Running ahead");
    digitalWrite(m1_a,HIGH);
    digitalWrite(m1_b,LOW);
    digitalWrite(m2_a,LOW);
    digitalWrite(m2_b,LOW);
    delay(2000);
    Serial.println("Reverse");
    digitalWrite(m1_a,LOW);
    digitalWrite(m1_b,HIGH);
    digitalWrite(m2_a,LOW);
    digitalWrite(m2_b,LOW);
    delay(2000);
  }
  digitalWrite(enable_run,LOW); // disable
  digitalWrite(enable_turn,LOW); // enable on
  delay(2000);
}
