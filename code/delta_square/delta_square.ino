#include <AccelStepper.h>
#include <MultiStepper.h>
#include<math.h>
long int tomovesteps[3];
float L =150;
float l =300;
float x;
float y;
float s;
float z;

float a=58.32;
float b=((sqrt(3))/2)*(45-103.32);
float c=(45-103.32)/2;
double theta1;
double theta2;
double theta3;

byte dir1pin=2;
byte step1Pin=3;     //motor 1

byte dir2pin=4; 
byte step2Pin=5;       //motor 2

byte dir3pin=6;   
byte step3Pin=7;        //motor 3

byte motor3ground=8;
//Limit switches
int pos1 = 53;      //LM 1
int sig1 = 51;

int pos2 = 47;      //LM 2
int neg2 = 45;
int sig2 = 43;

int pos3 = 39;      //LM 3
int neg3 = 37;
int sig3 = 35;

// float c_theta1=0;
// float c_theta2=0;
// float c_theta3=0;

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

    stepper1.setMaxSpeed(500); 
    stepper2.setMaxSpeed(500);
    stepper3.setMaxSpeed(500);
   
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

digitalWrite(dir1pin,HIGH); //setting motor dir
digitalWrite(dir3pin,HIGH);
digitalWrite(dir2pin,HIGH);
    delay(2000);
Home();
 
}

void loop() {
  Serial.println("Enter Top Left Coordinates");
  while(Serial.available()==0){}

  x=Serial.parseInt();
  y=Serial.parseInt();//+0.15


Serial.println("Enter Side Length");
  while(Serial.available()==0){}  
  s=Serial.parseInt();//+50     
z=-350;
Moveto(0,0,-300);           // Point A
delay(500);
if(checkworkvol(x,y,s)==1){
Moveto(x,y,z);           // Point A
delay(1000);
float d=s/8;
for(float i=x;i<=x+s;i=i+d){  
Moveto(i,y,z);
}
for(float i=y;i>=y-s;i=i-d){
  Moveto(x+s,i,z);
}
for(float i=x+s;i>=x;i=i-d){
  Moveto(i,y-s,z);
}
for(float i=y-s;i<=y;i=i+d){
  Moveto(x,i,z);
}
// Moveto(x,y,z);           // Point A
// delay(1000);

// for(int i=0;i<=2;i++){
// Moveto(x,y,z);           // Point A
// // delay(250);

// Serial.println(String(x)+" "+String(y));
// Serial.println("");

// Moveto(((2*x)+s)/2,y,z);     // Mid AB

// Serial.println(String(((2*x)+s)/2)+" "+String(y));
// Serial.println("");

// Moveto(x+s,y,z);         //Point B
// // delay(250);

// Serial.println(String(x+s)+" "+String(y));
// Serial.println("");

// Moveto(x+s,((2*y)-s)/2,z);   //Mid BC

// Serial.println(String(x+s)+" "+String(((2*y)-s)/2));
// Serial.println("");

// Moveto(x+s,y-s,z);       //Point C
// // delay(250);

// Serial.println(String(x+s)+" "+String(y-s));
// Serial.println("");

// Moveto(((2*x)+s)/2,y-s,z);   //Mid CD

// Serial.println(String(((2*x)+s)/2)+" "+String(y-s));
// Serial.println("");

// Moveto(x,y-s,z);        //Point D
// // delay(250);

// Serial.println(String(x)+" "+String(y-s));
// Serial.println("");

// Moveto(x,((2*y)-s)/2,z);    //Mid AD

// Serial.println(String(x)+" "+String(((2*y)-s)/2));
// Serial.println("");
// }
delay(500);
Moveto(0,0,-300); 
}
Serial.println("Coordinates out of Work Volume !");
}




bool checkworkvol(float x,float y,float s){
  if(abs(x+s)>100||abs(y-s)>100 || abs(x)>100||abs(y)>100){
    return 0;
  }
  else {
    return 1;
  }
}

void Moveto(int x,int y,int z){

theta1=angle_1(x,y,z);
theta2=angle_2(x,y,z);
theta3=angle_3(x,y,z);

Serial.println(-theta1);
Serial.println(-theta2);
Serial.println(-theta3);

if (isnan(theta1)!=1 && isnan(theta2)!=1  && isnan(theta3)!=1){
tomovesteps[0]=-theta1/0.1125;
tomovesteps[1]=-theta2/0.1125;
tomovesteps[2]=-theta3/0.1125;
Moveall.moveTo(tomovesteps);
Moveall.runSpeedToPosition();

}else{Serial.println("INVALID COORDINATES");}

}




double angle_1(float x,float y,float z){
  float u1 = 2 * 150 * (y + a);
  float v1= 2*L*z;  
  float w1 = pow(x,2) + pow(y,2) + pow(z,2) + pow(a,2) + pow(L,2)+ (2*y*a) - pow(l,2);
  float t1= (-v1 -sqrt(pow(u1, 2) + pow(v1, 2) - pow(w1, 2))) / (w1 - u1);
  float a1=(2*degrees(atan(t1)));
    return a1;
    }


double angle_2(float x,float y,float z){
    float u2 = -150*(sqrt(3)*(x+b)+y+c);
    float v2= 2*L*z;
    float w2 = pow(x,2) + pow(y,2) + pow(z,2) + pow(b,2) + pow(c,2) + pow(L,2) + (2*x*b) + (2*y*c) - pow(l,2);
    float t2= (-v2 - sqrt(pow(u2, 2) + pow(v2, 2) - pow(w2, 2))) / (w2 - u2);
    float a2=(2*degrees(atan(t2)));
    return a2;
}

double angle_3(float x,float y,float z){
    float u3= 150*(sqrt(3)*(x-b)-y-c);
    float v3= 2*L*z;
    float w3= pow(x,2) + pow(y,2) + pow(z,2) + pow(b,2) + pow(c,2) + pow(L,2) - (2*x*b) + (2*y*c) - pow(l,2);
    float t3=(-v3- sqrt(pow(u3, 2) + pow(v3, 2) - pow(w3, 2))) /(w3 - u3);
    float a3=(2*degrees(atan(t3)));
    return a3;
}





void Home(){
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

// s=100;
// d=s/5;
// for(float i=x;i<=x+s;i=i+d){  
// moveTo(i,y,z)
// }
// for(float i=y;i>=y-s;i=i-d){
//   moveTo(x+s,i,z)
// }
// for(float i=x+s;i>=x;i=i-d){
//   moveTo(i,y-s,z)
// }
// for(float i=y-s;i<=y;i=i+d){
//   moveTo(x,i,z)
// }

