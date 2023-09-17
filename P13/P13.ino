#include "BluetoothSerial.h"
BluetoothSerial BT;
const int pir=4; //D4 es el puerto digital para la entrada out del pir
const int led=5; //D5 es el puerto de led de presencia
void setup() {
Serial.begin(9600);
BT.begin("MI_ESP32_UTEQ");// Nombre del dispositivo Bluetooth que quieras asignarle
pinMode(pir, INPUT);
pinMode(led, OUTPUT);
digitalWrite(led,LOW);
}
void loop() {
int sensor;
sensor=digitalRead(pir); //lectura del pir
if(sensor==HIGH){
Serial.println("Ratero");
BT.println("Ratero");
digitalWrite(led, HIGH);
delay(100);
}else{
if(sensor==LOW){
Serial.println("No rata");
BT.println("No rata");
digitalWrite(led, LOW);
delay(100);
}
}
}
