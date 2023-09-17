#include <Servo.h> //librería para el ESP32Servo.h
Servo myservo;
int servomotor=14; //GPIO 4 puerto digital del servo motor
int pos = 0;
void setup() {
myservo.attach(servomotor); //inicializa el puerto digital para el servo motor
}
void loop() {
for (pos = 0; pos <= 180; pos += 1) {
// in steps of 1 degree
myservo.write(pos);
delay(10);
}
for (pos = 180; pos >= 0; pos -= 1) {
myservo.write(pos);
delay(10);
}
}
