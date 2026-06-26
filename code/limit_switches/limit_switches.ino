int a;


          // M1    M2   M3 
int pos=53; // 53    47    39
int neg=45; // GND   45    37
int sig=51; // 51    43    35

byte dir1pin = 2;
byte step1Pin = 3; // motor 1

byte dir2pin = 4;
byte step2Pin = 5; // motor 2

byte dir3pin = 6;
byte step3Pin = 7; // motor 3

byte motor3ground = 8;
void setup() {
  pinMode(step1Pin, OUTPUT);
  pinMode(dir1pin, OUTPUT);
  pinMode(step2Pin, OUTPUT);
  pinMode(dir2pin, OUTPUT);
  pinMode(step3Pin, OUTPUT);
  pinMode(dir3pin, OUTPUT);
  pinMode(motor3ground, OUTPUT);
  digitalWrite(dir1pin,HIGH);

  digitalWrite(motor3ground, LOW);
pinMode(pos,OUTPUT);
pinMode(neg,OUTPUT);
pinMode(sig,INPUT);


digitalWrite(pos,HIGH);
digitalWrite(neg,LOW);

Serial.begin(9600);

}

void loop() {
a=digitalRead(sig);
Serial.println(a);
if(a==1){
  while(1){}
}
  digitalWrite(step1Pin,HIGH);
   delayMicroseconds(1000);
   digitalWrite(step1Pin,LOW);
   delayMicroseconds(1000);
}



//red purple grey