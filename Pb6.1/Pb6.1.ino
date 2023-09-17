#include <Servo.h> //librería para el ESP32Servo.h
Servo myservo;
int servomotor=4; //GPIO 4 puerto digital del servo motor
int pos = 0;
const int pir=19;
void setup() {
  Serial.begin(9600);
myservo.attach(servomotor); //inicializa el puerto digital para el servo motor
pinMode(pir, INPUT);
}
void loop() {

  int sensor;
sensor=digitalRead(pir); //lectura del pir
if(sensor==HIGH){
Serial.println("Ratero");
myservo.write(90);
delay(10);
 myservo.write(0);
delay(10);
delay(1000);
}else{
if(sensor==LOW){
Serial.println("No rata");
 myservo.write(0);
delay(10);
delay(1000);
}
}
delay(100);

}
