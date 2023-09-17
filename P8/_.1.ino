#include <Adafruit_Sensor.h>
#include <DHT.h>
const int DHTPIN=15;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); // dht(puerto, dispositivo) instancia de la clase DHT
void setup() {
Serial.begin(9600);
Serial.println("Prueba DHT");
dht.begin(); // inicializa el sensor.
}
void loop() {
delay(2000); //requiere de dos segundos para realizar la lectura.
float h = dht.readHumidity(); // Método readHumedity() para obtener la humedad ambiente
float t = dht.readTemperature(); // Métod readTemperature() obtiene la temperatura
if (isnan(h) || isnan(t)) { // isnan() verifica que lleguen los dos valores
Serial.println(F("Falla en la lectura del sensor, verifica librería y conexión"));
return;
}
Serial.print("Humedad: ");
Serial.print(h);
Serial.print("% Temperatura: ");
Serial.print(t);
Serial.println("°C ");
delay(1000);
}
