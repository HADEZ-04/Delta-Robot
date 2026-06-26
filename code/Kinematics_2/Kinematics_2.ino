float L =150;
float l =300;
float x;
float y;
float z;
float a=58.32;
float b=((sqrt(3))/2)*(45-103.32);
float c=(45-103.32)/2;
double theta1;
double theta2;
double theta3;
struct Cord{
  float a1;
  float a2;
  float a3;
};

void setup() {
Serial.begin(9600);
}




void loop() {

Serial.println("Enter Coordinates");
 
while(Serial.available()==0){}

  x=Serial.parseInt();
  y=Serial.parseInt();//+0.15
  z=Serial.parseInt()+50.5;//+50         
  
Cord var=kinematics(x,y,z);

theta1=var.a1;
theta2=var.a2;
theta3=var.a3;


if (isnan(theta1)!=1 && isnan(theta2)!=1  && isnan(theta3)!=1){
Serial.println(-theta1);
Serial.println(-theta2);
Serial.println(-theta3);

}else{Serial.println("INVALID COORDINATES");}

}



Cord kinematics(float x,float y,float z){
    float u1 = 2 * 150 * (y + a);
    float v1= 2*L*z;  
    float w1 = pow(x,2) + pow(y,2) + pow(z,2) + pow(a,2) + pow(L,2)+ (2*y*a) - pow(l,2);
    float t1= (-v1 -sqrt(pow(u1, 2) + pow(v1, 2) - pow(w1, 2))) / (w1 - u1);
    float a1=(2*degrees(atan(t1)));
    
    float u2 = -150*(sqrt(3)*(x+b)+y+c);
    float v2= 2*L*z;
    float w2 = pow(x,2) + pow(y,2) + pow(z,2) + pow(b,2) + pow(c,2) + pow(L,2) + (2*x*b) + (2*y*c) - pow(l,2);
    float t2= (-v2 - sqrt(pow(u2, 2) + pow(v2, 2) - pow(w2, 2))) / (w2 - u2);
    float a2=(2*degrees(atan(t2)));

    float u3= 150*(sqrt(3)*(x-b)-y-c);
    float v3= 2*L*z;
    float w3= pow(x,2) + pow(y,2) + pow(z,2) + pow(b,2) + pow(c,2) + pow(L,2) - (2*x*b) + (2*y*c) - pow(l,2);
    float t3=(-v3- sqrt(pow(u3, 2) + pow(v3, 2) - pow(w3, 2))) /(w3 - u3);
    float a3=(2*degrees(atan(t3)));
    return {a1,a2,a3};
}

