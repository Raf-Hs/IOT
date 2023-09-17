const int Led=19;
// puerto GPIO22 (PIN D22)
void setup() {
Serial.begin(9600);
pinMode(Led,OUTPUT);
pinMode(Led2,OUTPUT);
}
void loop() {
digitalWrite(Led,HIGH);
digitalWrite(Led2,HIGH);
Serial.println("El led prende");
delay(1000);

digitalWrite(Led,LOW);
digitalWrite(Led2,LOW);
Serial.println("El led apaga");
delay(1000);
} 