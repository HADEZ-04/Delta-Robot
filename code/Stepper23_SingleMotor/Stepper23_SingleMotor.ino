
#include <Stepper.h>
String a;
int current_pos;
int pos;

byte dir1pin=2;
byte step1Pin=3;     //motor 1

byte dir2pin=4; 
byte step2Pin=5;       //motor 1

byte dir3pin=6;   
byte step3Pin=7;        //motor 1

byte motor3ground=8;

void setup() {
    pinMode(step1Pin,OUTPUT); 
    pinMode(dir1pin,OUTPUT);

    pinMode(step2Pin,OUTPUT); 
    pinMode(dir2pin,OUTPUT);

    pinMode(step3Pin,OUTPUT); 
    pinMode(dir3pin,OUTPUT); 
    pinMode(motor3ground,OUTPUT); 
    digitalWrite(motor3ground,LOW);


    Serial.begin(9600);

current_pos=0;
}

void loop() {
  
if(Serial.available()>0){
 a=Serial.readString();
 pos=a.toInt()/0.1125;

   if(pos - current_pos>0){
  digitalWrite(dir2pin,HIGH);
  for(int i=0;i<pos-current_pos;i++){
  digitalWrite(step2Pin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(step2Pin,LOW); 
  delayMicroseconds(1000);}
  }

  else if(pos - current_pos<0){
  digitalWrite(dir2pin,LOW);
  for(int j=0;j<-1*(pos - current_pos);j++){
  digitalWrite(step2Pin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(step2Pin,LOW); 
  delayMicroseconds(1000);
  }
}}
current_pos=pos;
}




