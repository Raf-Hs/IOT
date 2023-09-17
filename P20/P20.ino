#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); // dht(puerto, dispositivo) instancia de la
//clase DHT
const int relay=22;
const int Led1=19; // puerto GPIO22 (PIN D22)
const int Led2=21; // puerto GPIO22 (PIN D22)
void setup() {
Serial.begin(9600);
pinMode(Led1,OUTPUT);
pinMode(Led2,OUTPUT);
pinMode(relay,OUTPUT); // puerto GPIO digital que va al Sorce //del Relay
Serial.println("Prueba DHT");
dht.begin(); // inicializa el sensor.
}
void loop() {
delay(2000); //requiere de dos segundos para realizar la lectura. 
float h = dht.readHumidity(); // Método readHumedity() para obtener la
//humedad //ambiente
float t = dht.readTemperature(); // Método readTemperature() obtiene la
//temperatura
if(isnan(h) || isnan(t)) { // isnan() verifica que lleguen los dos valores
Serial.println(F("Falla en la lectura del sensor, verifica librería y conexión"));
return;
}
Serial.print(h); //se imprime la temperatura en el serial
Serial.println("%");
Serial.print(t); //se imprime la temperatura en el serial
Serial.println("°C");
if(t>=25.0 && t<=37.0){ // si la temperatura es mayor o igual a 30 //grados
digitalWrite (relay,HIGH);
digitalWrite (Led1,HIGH);
digitalWrite (Led2,LOW);
delay(1000);

 digitalWrite (relay,LOW);
 digitalWrite (Led1,LOW);
 digitalWrite (Led2,HIGH);
delay(1000); //enciende el motor al mandar un alto 
}else{ //al puerto de salida donde está conectado el relay. 
 digitalWrite(relay,LOW);
// si la temperatura no está en este rango se //apaga.
} // fin de if
delay(10); // se espera dos segundos para hacer la lectura
}
