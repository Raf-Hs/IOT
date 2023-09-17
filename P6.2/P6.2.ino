#include <Arduino_JSON.h>
#include <AzureIotHub.h>
#include <Esp32MQTTClient.h>
#include <ArduinoOTA.h>
#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <WiFi.h>

int led=23;
int boton=22;
int otro;
const char *ssid = "UTEQ-Alumnos";
const char *password = "";
const char* serverName = "http://10.13.13.111/enviardatos2.php";

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
int estado;
int valor;
int tem;
valor=digitalRead(boton);
if(valor == 1){
digitalWrite(led, HIGH);
estado=1;
}else{
digitalWrite(led, LOW);
estado=0;

}
otro=12; // este puede ser el valor de otro sensor
if(WiFi.status()== WL_CONNECTED){
HTTPClient http;
// Su nombre de dominio con la ruta del URL o la dirección IP
http.begin(serverName);
// Especifica content-type header
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
// Prepara el HTTP POST para enviar los datos del boton y otro valor de un sensor
// otro valor.
String httpRequestData="&valor="+ String(estado)+ "&otro=" + String(otro)+ "";
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
