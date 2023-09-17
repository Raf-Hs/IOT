void setup() {
Serial.begin(9600);
for(int i=21;i<=23;i++){
pinMode(i,OUTPUT);
}
}
void loop() {
int opcion;
if(Serial.available()>0){
opcion=Serial.parseInt();
switch(opcion){
case 1: digitalWrite(21,HIGH);
delay(2000);
digitalWrite(21,LOW);
delay(2000);
break;
case 2: digitalWrite(22,HIGH);
delay(2000);
digitalWrite(22,LOW);
delay(2000);
break;
case 3: digitalWrite(23,HIGH);
delay(2000);
digitalWrite(23,LOW);
delay(2000);
break;
}
}
}
