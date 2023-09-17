void setup() {
Serial.begin(9600);
for(int i=21;i<=23;i++){
pinMode(i,OUTPUT);
}
}
void loop() {
for(int i=21;i<=23;i++){
digitalWrite(i,HIGH);
delay(500);
digitalWrite(i,LOW);
delay(500);
}
}
