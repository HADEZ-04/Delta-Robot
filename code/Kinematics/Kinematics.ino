#include<math.h>
float L =150;
float l =300;
float x=95.11;
float y=30.90;
float z=-350;
float a =58.32;
float b = ((sqrt(3))/2)*(45-103.32);
float c= (45-103.32)/2;

void setup() {
Serial.begin(9600);

double theta1 = angle_1();

double theta2= angle_2();

double theta3=angle_3();


Serial.println(-theta1);
Serial.println(-theta2);
Serial.println(-theta3);
}

void loop() {
  // put your main code here, to run repeatedly:

}



float angle_1(){
  float u1 = 2 * 150 * (y + a);
    float v1= 2*L*z;  
   float w1 = pow(x,2) + pow(y,2) + pow(z,2) + pow(a,2) + pow(L,2)+ (2*y*a) - pow(l,2);
    float t1= (-v1 -sqrt(pow(u1, 2) + pow(v1, 2) - pow(w1, 2))) / (w1 - u1);
    float a1=(2*degrees(atan(t1)));
    return a1;
    }


double angle_2(){
    float u2 = -150*(sqrt(3)*(x+b)+y+c);
    float v2= 2*L*z;
    float w2 = pow(x,2) + pow(y,2) + pow(z,2) + pow(b,2) + pow(c,2) + pow(L,2) + (2*x*b) + (2*y*c) - pow(l,2);
    float t2= (-v2 - sqrt(pow(u2, 2) + pow(v2, 2) - pow(w2, 2))) / (w2 - u2);
    float a2=(2*degrees(atan(t2)));
    return a2;
}

double angle_3(){
    float u3= 150*(sqrt(3)*(x-b)-y-c);
    float v3= 2*L*z;
    float w3= pow(x,2) + pow(y,2) + pow(z,2) + pow(b,2) + pow(c,2) + pow(L,2) - (2*x*b) + (2*y*c) - pow(l,2);
    float t3=(-v3- sqrt(pow(u3, 2) + pow(v3, 2) - pow(w3, 2))) /(w3 - u3);
    float a3=(2*degrees(atan(t3)));
    return a3;
}







