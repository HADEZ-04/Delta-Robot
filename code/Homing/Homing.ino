#include <AccelStepper.h>
#include <MultiStepper.h>


long int tomovesteps[3];

//Motor pins
byte dir1pin = 2;
byte step1Pin = 3; // motor 1

byte dir2pin = 4;
byte step2Pin = 5; // motor 2

byte dir3pin = 6;
byte step3Pin = 7; // motor 3

byte motor3ground = 8;

//Limit switches
int pos1 = 53;      //LM 1
int sig1 = 51;

int pos2 = 47;      //LM 2
int neg2 = 45;
int sig2 = 43;

int pos3 = 39;      //LM 3
int neg3 = 37;
int sig3 = 35;


void setup() {
  Serial.begin(9600);

  pinMode(step1Pin, OUTPUT);
  pinMode(dir1pin, OUTPUT);
  pinMode(step2Pin, OUTPUT);
  pinMode(dir2pin, OUTPUT);
  pinMode(step3Pin, OUTPUT);
  pinMode(dir3pin, OUTPUT);
  pinMode(motor3ground, OUTPUT);

  digitalWrite(motor3ground, LOW);

  pinMode(pos1, OUTPUT);
  pinMode(sig1,INPUT);

  pinMode(pos2, OUTPUT);
  pinMode(neg2, OUTPUT);
  pinMode(sig2, INPUT);
  pinMode(pos3, OUTPUT);
  pinMode(neg3, OUTPUT);
  pinMode(sig3, INPUT);

  digitalWrite(pos1, HIGH);

  digitalWrite(pos2, HIGH);
  digitalWrite(neg2, LOW);
 
  digitalWrite(pos3, HIGH);
  digitalWrite(neg3, LOW);

digitalWrite(dir1pin,HIGH); //setting motor dir
digitalWrite(dir3pin,HIGH);
digitalWrite(dir2pin,HIGH);

  delay(2000);
  home(); 
}

void loop() {


}





void home(){
int del=1000;
while(digitalRead(sig1)==0 || digitalRead(sig2)==0 || digitalRead(sig3)==0){

  if(digitalRead(sig1)==0){
   digitalWrite(step1Pin,HIGH);
   delayMicroseconds(del);
   digitalWrite(step1Pin,LOW);
   delayMicroseconds(del);
      }

  if(digitalRead(sig2)==0){
   digitalWrite(step2Pin,HIGH);
   delayMicroseconds(del);
   digitalWrite(step2Pin,LOW);
   delayMicroseconds(del);

      }
  if(digitalRead(sig3)==0){
   digitalWrite(step3Pin,HIGH);
   delayMicroseconds(del);
   digitalWrite(step3Pin,LOW);
   delayMicroseconds(del);
      }
}
}



