int vector[]={21,22,23};
void setup() {
Serial.begin(9600);
for(int i=0;i<3;i++){
pinMode(vector[i],OUTPUT);
}
}
void loop() {
for(int i=0;i<3;i++){
digitalWrite(vector[i],HIGH);
delay(1000);
digitalWrite(vector[i], LOW);

delay(1000);
}
}
