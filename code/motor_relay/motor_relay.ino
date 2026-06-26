char a;
int m1=7;
int m2=8;
void setup() {
pinMode(m2,OUTPUT);
pinMode(m1,OUTPUT);

digitalWrite(m2,HIGH);
digitalWrite(m1,HIGH);

Serial.begin(9600);
}

void loop() {
if(Serial.available()>0){
  a=Serial.read();
  if(a=='1'){
    digitalWrite(m1,LOW);
  }else if(a=='0'){
        digitalWrite(m1,HIGH);

  }
  else if(a=='2'){
        digitalWrite(m2,LOW);
  }
    else if(a=='3'){
        digitalWrite(m2,HIGH);
  }
}
}
