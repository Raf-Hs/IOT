void setup() {
Serial.begin(9600);
int i=21;
while(i<=23){
pinMode(i,OUTPUT);
i++;
}
i=21;
while(i<=23){
digitalWrite(i,LOW);
i++;
}
}
void loop() {
int i=21;
while(i<=23){
digitalWrite(i,HIGH);
delay(500);

digitalWrite(i,LOW);
delay(500);
i++;
}
}
