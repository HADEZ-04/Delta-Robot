#include <AccelStepper.h>
#include <MultiStepper.h>
#include<math.h>

long int tomovesteps[3];
float L =150;
float l =300;

float a=58.32;
float b=((sqrt(3))/2)*(45-103.32);
float c=(45-103.32)/2;

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
 Serial.println("");
 Serial.print("Enter Speed : ");
  while(Serial.available()==0){}
  int speed=Serial.parseInt();
  int a=Serial.read(); 
  
  stepper1.setMaxSpeed(speed); 
  stepper2.setMaxSpeed(speed);
  stepper3.setMaxSpeed(speed);  
 
 Serial.println(speed);

// delay(500);
// Moveto(0,0,-300);
  switch(Selectop()){
  case 0:
    Home();
    break;
  case 1:
     PNP();
     break;
  case 2:
     Square();
     break;
  case 3:
     Circle();
     break;
  default:
     Serial.println("Invalid");
     break;   }

}



int Selectop(){
  Serial.println("Select the Operation :");
  Serial.println("");
  Serial.println("1 : Pick And Place");
  Serial.println("2 : Square");
  Serial.println("3 : Circle");
  while(Serial.available()==0){}
  int a= Serial.parseInt();
  int temp= Serial.read();
    return a;
  }



void Moveto(float x,float y,float z){
double theta1;
double theta2;
double theta3;

theta1=angle_1(x,y,z);
theta2=angle_2(x,y,z);
theta3=angle_3(x,y,z);
// Serial.println(-theta1);
// Serial.println(-theta2);
// Serial.println(-theta3);
if (isnan(theta1)!=1 && isnan(theta2)!=1  && isnan(theta3)!=1){
tomovesteps[0]=-theta1/0.1125;
tomovesteps[1]=-theta2/0.1125;
tomovesteps[2]=-theta3/0.1125;
Moveall.moveTo(tomovesteps);
Moveall.runSpeedToPosition();
}else{Serial.println("INVALID COORDINATES");}

}
//Kinematics
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


//Homing
void Home(){
int delay=1000;
Serial.println("Homing..");  
while(digitalRead(sig1)==0 || digitalRead(sig2)==0 || digitalRead(sig3)==0){

Serial.println(digitalRead(sig1));
  if(digitalRead(sig1)==0){
   digitalWrite(step1Pin,HIGH);
   delayMicroseconds(delay);
   digitalWrite(step1Pin,LOW);
   delayMicroseconds(delay);
      }
  if(digitalRead(sig2)==0){
   digitalWrite(step2Pin,HIGH);
   delayMicroseconds(delay);
   digitalWrite(step2Pin,LOW);
   delayMicroseconds(delay);
      }
  if(digitalRead(sig3)==0){
   digitalWrite(step3Pin,HIGH);
   delayMicroseconds(delay);
   digitalWrite(step3Pin,LOW);
   delayMicroseconds(delay);
      }
}
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);
}

//Pick n Place
void PNP(){
float x,y,z,x1,y1,z1,l;  

Serial.println("");
Serial.print("Enter Pick Coordinates : ");
while(Serial.available()==0){}

  x=Serial.parseFloat();
  y=Serial.parseFloat();//+0.15
  z=Serial.parseFloat()+50;//+50  
  int c=Serial.read();   
Serial.println(String(x)+","+String(y)+","+String(z-50));

Serial.print("Enter Place Coordinates : ");
while(Serial.available()==0){}

  x1=Serial.parseFloat();
  y1=Serial.parseFloat();//+0.15
  z1=Serial.parseFloat()+50;//+50   
    int b=Serial.read();   
 
Serial.println(String(x1)+","+String(y1)+","+String(z1-50));

Serial.print("Enter No.of loops : ");
 while(Serial.available()==0){}
    l=Serial.parseInt();
Serial.println(l);

delay(250);
Moveto(0,0,-300);
for(int i=0;i<l;i++){
delay(250);  
Moveto(0,0,-300);
delay(250);
Moveto(x,y,z);
delay(250);
Moveto(0,0,-300);
delay(250);
Moveto(x1,y1,z1);
}
delay(500);
Moveto(0,0,-300);
}
//Square
void Square(){
float x,y,z,s,l;
Serial.println("");
Serial.print("Enter Top Left Corner Coordinates :");
while(Serial.available()==0){}

  x=Serial.parseFloat();
  y=Serial.parseFloat();//+0.15
    int temp=Serial.read();   

Serial.println(String(x)+","+String(y));

Serial.print("Enter Side Length : ");
while(Serial.available()==0){}  
  s=Serial.parseFloat();//+50  
    int d=Serial.read();   
Serial.println(s);

Serial.print("Enter No.of loops : ");
while(Serial.available()==0){}
    l=Serial.parseInt();  
      int e=Serial.read();   

Serial.println(l);
z=-350;
delay(250);
Moveto(0,0,-300);
delay(500);
if(checkworkvol_S(x,y,s)==1){  
Moveto(x,y,z);           // Point A
delay(500);
float d=s/8;
for(int j=0;j<l;j++){
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
}}}
else{Serial.println("Coordinates out of Work Volume !");}
delay(500);
Moveto(0,0,-300);
}


void Circle(){
float k,h,r,z,l;
float x[70];
float y[70];
int j=0;
int v=0;
Serial.println("");
Serial.print("Enter Centre Coordinates : ");
while(Serial.available()==0){}

k=Serial.parseFloat();
h=Serial.parseFloat();//+0.15
  int temp=Serial.read();   

Serial.println(String(k)+","+String(h));

Serial.print("Enter Radius : ");
while(Serial.available()==0){}  
r=Serial.parseFloat();//+50   
  int as=Serial.read();   

Serial.println(r);

Serial.print("Enter No.of loops : ");
while(Serial.available()==0){}
  l=Serial.parseInt(); 
    int sd=Serial.read();   

Serial.println(l);

z=-350;
delay(250);
Moveto(0,0,-300);
delay(250);
for(int i=0;i<30;i++){
x[i]=k+(r*cos(j*(M_PI/180)));
y[i]=h+(r*sin(j*(M_PI/180)));
if(checkworkvol_C(x[i],y[i])==0){ v=1; }
j=j+12 ;
}

if(v==0){ 
Moveto(x[0],y[0],z);
delay(1000);
for(int j=0;j<l;j++){
 for(int i=0;i<30;i++){
 Moveto(x[i],y[i],z);
  }}

}
else {Serial.println("Coordinates out of Work Volume !");}
delay(500);
Moveto(0,0,-300);
}


bool checkworkvol_S(float x,float y,float s){
  if(abs(x+s)>100||abs(y-s)>100 || abs(x)>100||abs(y)>100) { return 0; }
  else { return 1; }}
bool checkworkvol_C(float x,float y){
  if(abs(x)>100||abs(y)>100) { return 0; }
  else { return 1; }
}