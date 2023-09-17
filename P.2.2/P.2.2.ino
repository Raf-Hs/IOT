const int led1=21;
int led2=22;
int led3=23;
const String opcion;
void setup() {
Serial.begin(9600);
for(int i=21;i<=23;i++){
pinMode(i,OUTPUT);
}
}
void loop() {
char opcion;
if(Serial.available()>0){
opcion=Serial.read();
switch(opcion){

case 'A': digitalWrite(21,HIGH);
delay(2000);
digitalWrite(21,LOW);
delay(2000);
break;

case 'B': digitalWrite(22,HIGH);
delay(2000);
digitalWrite(22,LOW);
delay(2000);
break;

case 'C': digitalWrite(23,HIGH);
delay(2000);
digitalWrite(23,LOW);
delay(2000);
break;
}
}
}
