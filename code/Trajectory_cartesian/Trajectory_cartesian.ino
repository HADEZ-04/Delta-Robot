#include <AccelStepper.h>
#include <MultiStepper.h>
#include<math.h>
long int tomovesteps[3];
float L =150;
float l =300;
float xi=-50;
float y=0;
float z=-350+50;
float xf=50;
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

float c_theta1=0;
float c_theta2=0;
float c_theta3=0;

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

digitalWrite(dir1pin,HIGH); //setting motor dir
digitalWrite(dir3pin,HIGH);
digitalWrite(dir2pin,HIGH);
//     delay(3000);
// Home();
// delay(2000);
// tomovesteps[0]=-angle_1(xi,y,z)/0.1125;
// tomovesteps[1]=-angle_2(xi,y,z)/0.1125;
// tomovesteps[2]=-angle_3(xi,y,z)/0.1125;
// Moveall.moveTo(tomovesteps);
// Moveall.runSpeedToPosition();  
 
// delay(3000);
for(float i=xi;i<=xf;){  
Serial.print(angle_1(i,y,z));
Serial.print("  ");
Serial.print(angle_2(i,y,z));
Serial.print("  ");
Serial.println(angle_3(i,y,z));

tomovesteps[0]=-angle_1(i,y,z)/0.1125;
tomovesteps[1]=-angle_2(i,y,z)/0.1125;
tomovesteps[2]=-angle_3(i,y,z)/0.1125;
Moveall.moveTo(tomovesteps);
Moveall.runSpeedToPosition();  
i=i+10;
}
}

void loop() {

}


// int getcord(){
//   Serial.println("Enter PICK Coordinates");      
//  while(Serial.available()==0){} 
//   xi=Serial.parseInt();
//   yi=Serial.parseInt();//+0.15
//   zi=Serial.parseInt();//+50  

// Serial.println("Enter PLACE Coordinates");      
//   while(Serial.available()==0){} 
//   xf=Serial.parseInt();
//   yf=Serial.parseInt();//+0.15
//   zf=Serial.parseInt();//+50

// }


//inverse kinematics
float angle_1(float x,float y,float z){
  float u1 = 2 * L * (y + a);
    float v1= 2*L*z;  
   float w1 = pow(x,2) + pow(y,2) + pow(z,2) + pow(a,2) + pow(L,2)+ (2*y*a) - pow(l,2);
    float t1= (-v1 -sqrt(pow(u1, 2) + pow(v1, 2) - pow(w1, 2))) / (w1 - u1);
    float a1=(2*degrees(atan(t1)));
    return a1;
    }
float angle_2(float x,float y,float z){
    float u2 = -150*(sqrt(3)*(x+b)+y+c);
    float v2= 2*L*z;
    float w2 = pow(x,2) + pow(y,2) + pow(z,2) + pow(b,2) + pow(c,2) + pow(L,2) + (2*x*b) + (2*y*c) - pow(l,2);
    float t2= (-v2 - sqrt(pow(u2, 2) + pow(v2, 2) - pow(w2, 2))) / (w2 - u2);
    float a2=(2*degrees(atan(t2)));
    return a2;
}
float angle_3(float x,float y,float z){
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
