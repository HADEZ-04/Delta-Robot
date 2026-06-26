float L =150;
float l =300;

float x[10];
float y[10];
float z[10];

int n;
float a=58.32;
float b=((sqrt(3))/2)*(45-103.32);
float c=(45-103.32)/2;
double theta1[10];
double theta2[10];
double theta3[10];

float p,q,r;

void setup() {
Serial.begin(9600);
}




void loop() {
// n=getcord();
// Trajectory(theta1);
// Serial.println("");
// Trajectory(theta2);
// Serial.println("");
// Trajectory(theta;
// Serial.println("");
printTheta();

  
 }  
 




void printTheta(){
  int n=getcord();
  for (int i=0;i<=n;i++){
    Serial.print(theta1[i]);
    Serial.print("  ");
    Serial.print(theta2[i]);
    Serial.print("  ");
    Serial.println(theta3[i]);
}
}


int getcord(){
 float x,y,z; 
  Serial.println("Enter PICK Coordinates");      
 while(Serial.available()==0){} 
  x=Serial.parseInt();
  y=Serial.parseInt();//+0.15
  z=Serial.parseInt();//+50  
theta1[0]=angle_1(x,y,z);
theta2[0]=angle_2(x,y,z);
theta3[0]=angle_3(x,y,z);

Serial.println("Enter PLACE Coordinates");      
  while(Serial.available()==0){} 
  x=Serial.parseInt();
  y=Serial.parseInt();//+0.15
  z=Serial.parseInt();//+50
Serial.println("Enter No of Waypoints");  
  while(Serial.available()==0){} 
  int n=Serial.parseInt();
  theta1[n+1]=angle_1(x,y,z);
  theta2[n+1]=angle_2(x,y,z);
  theta3[n+1]=angle_3(x,y,z);

Serial.println("Enter the Waypoint coordinates");
 for(int i=1;i<=n;i++){
    while(Serial.available()==0){} 
      x=Serial.parseInt();
      y=Serial.parseInt();//+0.15
      z=Serial.parseInt();//+50
      theta1[i]=angle_1(x,y,z);
      theta2[i]=angle_2(x,y,z);
      theta3[i]=angle_3(x,y,z);

 }
 return n+1;
}


void Trajectory(double THETA[10]){
float t,d,k,angle;
  for (int j=0;j<=n;j++){       
   d=THETA[j]-THETA[j-1];            //difference b/w points
   t=abs(d/(90));                    //time taken 
     for(int i=0;i<=(t*100);i++){    //incrementing t by 0.01 and substituing in cubic eqn 
      k=i/100.0;
      angle=Cubic(j,d,t,k,THETA[j-1]);                                     
      Serial.println(angle);
}}
}


float Cubic(int j,float d,float t,float k,float THETA){   
   float a0=THETA;
   float vi=0;
   float vf=0;

  float a1=vi;
  float a2=(3*(d/pow(t,2)))-(2*vi-vf)/t;
  float a3=-(2*(d/pow(t,3)))+(vf+vi)/pow(t,2);

  return a0+(a1*k)+(a2*pow(k,2))+a3*pow(k,3);
}


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


