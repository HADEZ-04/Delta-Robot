#include <AccelStepper.h>
#include <MultiStepper.h>
#include<math.h>
long int tomovesteps[1];


byte dir1pin=A4;
byte step1Pin=A3;     //motor 1





AccelStepper stepper1 (AccelStepper::DRIVER,step1Pin,dir1pin);

MultiStepper Moveall;

void setup() {
  Serial.begin(9600);

    pinMode(step1Pin,OUTPUT); 
    pinMode(dir1pin,OUTPUT);

    stepper1.setMaxSpeed(800); 

   
    Moveall.addStepper(stepper1);



digitalWrite(dir1pin,HIGH); //setting motor dir

tomovesteps[0]=800;

Moveall.moveTo(tomovesteps);
Moveall.runSpeedToPosition(); 
}

void loop() {





}