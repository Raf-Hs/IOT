void setup() {
Serial.begin(9600);
for(int i=21;i<=23;i++){
pinMode(i,OUTPUT);
}
}
void loop() {
int i=21;
do{
digitalWrite(i,HIGH);
delay(500);
digitalWrite(i,LOW);
delay(500);
i++;
}while(i<=23);
}
