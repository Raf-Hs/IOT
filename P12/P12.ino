#include "BluetoothSerial.h"
BluetoothSerial BT; // BT es instancia de la clase BluetoothSerial
int Rele = 22; //puerto GPIO 22 para control del Relé
int estado; // Variable que toma la lectura que vienen del móvil
void setup() {
Serial.begin(9600); //se inicializa la comunicación serial
BT.begin("MI_ESP32_UTEQ");// Nombre del dispositivo Bluetooth en el móvil
pinMode(Rele, OUTPUT); // puerto 22 como salida para enviar 1 para encender y 0

digitalWrite(Rele, LOW); //iniciamos el relé en bajo
}
void loop() {
while(BT.available()>0){ //verificamos que recibimos datos por el serial
estado = BT.parseInt(); // si es verdadero, se lee la entrada y se convierte a entero
Serial.print(estado); // se asigna a la variable estado y se ve el dato en el monitor serial.
if(estado == 1){ // si llega un uno se enciende el relé y opera el motor
digitalWrite(Rele, HIGH); //relé en alto y cierra el interruptor NO
}else{ // si no
if (estado== 0){ // si el estado es igual a cero
digitalWrite(Rele, LOW); // el relé se apaga
}
} // fin del else
} // fin de while
delay(10); // se espera 10 milisegundos
}
