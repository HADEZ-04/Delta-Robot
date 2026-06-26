#include <AccelStepper.h>
#include <MultiStepper.h>
#include<math.h>
long int tomovesteps[1];


byte dir1pin=A4;
byte step1Pin=A3;     //motor 1

float theta1,theta2,THETA,j,t,d;
float a1,a2,a3;
AccelStepper stepper1 (AccelStepper::DRIVER,step1Pin,dir1pin);

MultiStepper Moveall;
void setup() {
Serial.begin(9600);

    pinMode(step1Pin,OUTPUT); 
    pinMode(dir1pin,OUTPUT);

    stepper1.setMaxSpeed(800);    
    Moveall.addStepper(stepper1);
    digitalWrite(dir1pin,HIGH); //setting motor dir

}

void loop() {
Serial.println("Enter theta1 and theta2");
while(Serial.available()==0){}

  theta1=Serial.parseInt();
  theta2=Serial.parseInt();//+0.15   //input  two angles

  d=theta2-theta1;      //difference between the angles
  t=abs(d/(90));                  //time the motor takes to achieve the final angle
  Serial.println(t);

  // Cubic Variables
  a1=theta1;
  a2=3*(d/pow(t,2));
  a3=2*(d/pow(t,3));

for(int i=0;i<=(t*100);i++){
   j=i/100.0;                                      //incremeting t by 0.01



  THETA=theta1+(3*(d/pow(t,2))*pow(j,2))-(2*(d/pow(t,3))*pow(j,3));

  // Serial.println(start(j));
  tomovesteps[0]=THETA/0.1125;
Moveall.moveTo(tomovesteps);
Moveall.runSpeedToPosition(); 
}

}



float start(float j){
    float THETA=theta1+(3*(d/pow(t,2))*pow(j,2))-(2*(d/pow(t,3))*pow(j,3));
return THETA;
}
