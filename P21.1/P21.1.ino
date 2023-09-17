#include <HTTPClient.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); // dht(puerto, dispositivo) instancia de la
//clase DHT
const int relay=22;
const int led1=19;
const int l2=21;
int motor;
const char *ssid = "Antonio21";
const char *password = "Antonio21";
const char* serverName = "http://192.168.137.222  /p.php";
void setup() {
  Serial.begin(9600);
  Serial.print("Configurando el access point...");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFI connected");
Serial.print("IP: ");
Serial.println(WiFi.localIP());

pinMode(relay,OUTPUT); // puerto GPIO digital que va al Sorce //del Relay
pinMode(led1,OUTPUT);
pinMode(l2,OUTPUT);
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
if(t>=24.0 && t<=29.0){ // si la temperatura es mayor o igual a 30 //grados
  digitalWrite(l2,LOW);
 digitalWrite(led1,HIGH);
digitalWrite(relay,HIGH); // se enciende el motor al mandar un alto 
motor = 1;
}else{ //al puerto de salida donde está conectado el relay. 
  digitalWrite(led1,LOW);
  digitalWrite(l2,HIGH);
  digitalWrite(relay,LOW);
  motor = 2;
// si la temperatura no está en este rango se //apaga.
} // fin de if
if(WiFi.status()== WL_CONNECTED){
HTTPClient http;
// Su nombre de dominio con la ruta del URL o la dirección IP
http.begin(serverName);
// Especifica content-type header
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
// Prepara el HTTP POST para enviar los datos del boton y otro valor de un sensor
// otro valor.
String httpRequestData="&temperatura="+ String(t)+ "&humedad=" + String(h)+ "&motor="+String(motor)+"";
int httpResponseCode = http.POST(httpRequestData);
if (httpResponseCode>0) {
Serial.println("HTTP dato enviado");
delay(1000);
}
else {
Serial.print("Error de código: ");
Serial.println(httpResponseCode);
}
http.end();
}
else {
Serial.println("WiFi desconectado");
}
delay(100); // se espera dos segundos para hacer la lectura
}
