#include <AccelStepper.h>
#include <MultiStepper.h>
#include<math.h>
long int tomovesteps[1];
byte dir1pin=A4;
byte step1Pin=A3;     //motor 1
int n;
float theta[100];

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
Trajectory();
}



float Cubic(int j,float d,float t,float k){
   float vi=0;
   float vf=0;
   float a0=theta[j];
   if(n==1){
    vi=0;
    vf=0;
   }
   else if(n!=1&&j==0){
    vi=0;
    vf=90;
   }
   else if(n!=1 && j==n-1){
    vi=90;
    vf=0;
   }else {
    vi=90;
    vf=90;
   }

  float a1=vi;
  float a2=((3/pow(t,2))*d)-((2/t)*vi)-((1/t)*vf);

  float a3=-((2/pow(t,3))*d)+(1/pow(t,2))*(vf+vi);

  return a0+(a1*k)+(a2*pow(k,2))+a3*pow(k,3);
}




int Getangles(){                                         
Serial.println("Enter the Pick and Place points");       //input PICK N PLACE angle (initial and final angle)
while(Serial.available()==0){}
theta[0]=Serial.parseInt();                              //setting PICK angle
float x=Serial.parseInt();                               //storing PLACE angle in a dummy variable as total no of waypoints is not known yet 

Serial.println("Enter no of Waypoints");                 //input no. of waypoints
while(Serial.available()==0){}
int w=Serial.parseInt();
theta[w+1]=x;                                            //setting PLACE angle

Serial.println("Enter the angles");                      //input waypoints
for(int i=1;i<=w;i++){
while(Serial.available()==0){}
  theta[i]=Serial.parseInt();
  }
  return w+1;
}



void Trajectory(){
float t,d,k,angle;
  n=Getangles();
  for (int j=0;j<n;j++){       
   d=theta[j+1]-theta[j];            //difference b/w points
   t=abs(d/(90));                    //time taken 
     for(int i=0;i<=(t*100);i++){    //incrementing t by 0.01 and substituing in cubic eqn 
      k=i/100.0;
      angle=Cubic(j,d,t,k);                                     
      Serial.println(angle);
       tomovesteps[0]=angle/0.1125;
       Moveall.moveTo(tomovesteps);
       Moveall.runSpeedToPosition(); 
}}
}
