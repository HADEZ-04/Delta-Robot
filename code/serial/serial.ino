
int x,y,z;
String a,b,c;
void setup() {
pinMode(13,OUTPUT);
Serial.begin(9600);
}

void loop() {
while(Serial.available()==0){}
a=Serial.readStringUntil(',');
b=Serial.readStringUntil(',');
c=Serial.readStringUntil(',');

if(a=="30"&& b=="20"&& c=="10"){
    digitalWrite(13,HIGH);
}
else{
  digitalWrite(13,LOW);}
}