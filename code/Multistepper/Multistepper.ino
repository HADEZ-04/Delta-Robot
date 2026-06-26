#include <AccelStepper.h>
#include <MultiStepper.h>
#include<math.h>
long int tomovesteps[3];
byte dir1pin=2;
byte step1Pin=3;     //motor 1

byte dir2pin=4; 
byte step2Pin=5;       //motor 2

byte dir3pin=6;   
byte step3Pin=7;        //motor 3

byte motor3ground=8;
double theta1;
double theta2;
double theta3;

//Limit switches
int pos1 = 53;      //LM 1
int sig1 = 51;

int pos2 = 47;      //LM 2
int neg2 = 45;
int sig2 = 43;

int pos3 = 39;      //LM 3
int neg3 = 37;
int sig3 = 35;

float a=0;
float b=0;
float c=0;

AccelStepper stepper1 (AccelStepper::DRIVER,step1Pin,dir1pin);
AccelStepper stepper2 (AccelStepper::DRIVER,step2Pin,dir2pin);
AccelStepper stepper3 (AccelStepper::DRIVER,step3Pin,dir3pin); 
MultiStepper Moveall;
void setup() {
  Serial.begin(9600);

    pinMode(step1Pin,OUTPUT); 
    pinMode(dir1pin,OUTPUT);

    pinMode(step2Pin,OUTPUT); 
    pinMode(dir2pin,OUTPUT);

    pinMode(step3Pin,OUTPUT); 
    pinMode(dir3pin,OUTPUT); 
    pinMode(motor3ground,OUTPUT); 

    stepper1.setMaxSpeed(800); 
    stepper2.setMaxSpeed(800);
    stepper3.setMaxSpeed(800);
   
    Moveall.addStepper(stepper1);
    Moveall.addStepper(stepper2);
    Moveall.addStepper(stepper3);
   
    digitalWrite(motor3ground,LOW);

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

delay(2000);
home();
// tomovesteps[0]=theta1/0.1125;
// tomovesteps[1]=theta2/0.1125;
// tomovesteps[2]=theta3/0.1125;
 
// Moveall.moveTo(tomovesteps);
// Moveall.runSpeedToPosition();
}

void loop() {
  Serial.println("Enter angles");
  while(Serial.available()==0){}

  theta1=Serial.parseInt();
  theta2=Serial.parseInt();
  theta3=Serial.parseInt();

tomovesteps[0]=theta1/0.1125;
tomovesteps[1]=theta2/0.1125;
tomovesteps[2]=theta3/0.1125;
 
Moveall.moveTo(tomovesteps);
Moveall.runSpeedToPosition();
}



void home(){

digitalWrite(dir1pin,HIGH); //setting motor dir
digitalWrite(dir3pin,HIGH);
digitalWrite(dir2pin,HIGH);
while(digitalRead(sig1)==0 || digitalRead(sig2)==0 || digitalRead(sig3)==0){

  if(digitalRead(sig1)==0){
   digitalWrite(step1Pin,HIGH);
   delayMicroseconds(1000);
   digitalWrite(step1Pin,LOW);
   delayMicroseconds(1000);
      }

  if(digitalRead(sig2)==0){
   digitalWrite(step2Pin,HIGH);
   delayMicroseconds(1000);
   digitalWrite(step2Pin,LOW);
   delayMicroseconds(1000);

      }
  if(digitalRead(sig3)==0){
   digitalWrite(step3Pin,HIGH);
   delayMicroseconds(1000);
   digitalWrite(step3Pin,LOW);
   delayMicroseconds(1000);
      }
}
}

