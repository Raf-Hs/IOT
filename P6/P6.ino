#include <WiFi.h>
#include <HTTPClient.h>
int led=23;
int boton=22;
const char *ssid = "MEGACABLE-2.4G-32A5";
const char *password = "2S7xDhn38u";
const char* serverName = "http://192.168.100.3/enviardatos.php";

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
pinMode(boton,INPUT);
pinMode(led,OUTPUT);
}
void loop() {
int valor;
int estado;
valor=digitalRead(boton);
if( valor == 1){
digitalWrite(led, HIGH);
estado=1;
}else {
digitalWrite(led,LOW);
estado=0;
}
if(WiFi.status()== WL_CONNECTED){
HTTPClient http;
// Su nombre de dominio con la ruta del URL o la dirección IP
http.begin(serverName);
// Especifica content-type header
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
// Prepara el HTTP POST para solicitar dato
String httpRequestData = "&valor=" + String(estado) + ""; //concatenación de datos de los sensores al GBD

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
//delay(1000);
}
