#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
const int DHTPIN=15;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "MEGACABLE-2.4G-32A5";
const char* password = "2S7xDhn38u";
// +código internacional de LADA + número telefónico
// Méxicol +521, example: +521xxxxxxxxxx”
String phoneNumber = "5214427477664";
String apiKey = "9331869";
const int pir=15; //PUERTO GPIO 18 DEL PIR
void sendMessage(String mensaje){
// Data to send with HTTP POST
String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey +
"&text=" + urlEncode(mensaje);
WiFiClient client;
HTTPClient http;
http.begin(client, url);
// Specify content-type header
http.addHeader("Content-Type", "application/x-www-form-urlencoded");

// Send HTTP POST request
int httpResponseCode = http.POST(url);
if (httpResponseCode == 200){
Serial.print("Message sent successfully");
}
else{
Serial.println("Error sending the message");
Serial.print("HTTP response code: ");
Serial.println(httpResponseCode);
}
// Free resources
http.end();
}
void setup() {
Serial.begin(9600);
pinMode(pir,INPUT);
WiFi.begin(ssid, password);
Serial.println("Connecting");
while(WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");

Serial.println("Prueba DHT");
dht.begin(); // inicializa el sensor.
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());
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

if(h > 12){
sendMessage("Se tienen una temperatura agradable en casa");
delay(2000);
Serial.println("Mensaje enviado");
}
delay(2000);
}
