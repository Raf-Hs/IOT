#include <WiFi.h>
#include <HTTPClient.h>
const int pir=4; //D4 es el puerto digital para la entrada out del pir
const int led=5; //D5 es el puerto de led de presencia
const char *ssid = "MEGACABLE-2.4G-32A5";
const char *password = "2S7xDhn38u";
const char* serverName = "http://192.168.100.3/sensorpir.php";

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
pinMode(pir, INPUT);
pinMode(led, OUTPUT);
digitalWrite(led,LOW);
}
void loop() {
//--------------------------------------------------sensor PIR------------------------------
int sensor;
int estado;
sensor=digitalRead(pir); //lectura del pir
if(sensor==HIGH){
Serial.println("Ratero");
estado=1;
digitalWrite(led, HIGH);
delay(1000);
}else{
if(sensor==LOW){
Serial.println("No rata");
estado=0;
digitalWrite(led, LOW);
delay(1000);
}
}
delay(100);

//---------------------------------------------fin de script sensor pir-----------------------------------
if(WiFi.status()== WL_CONNECTED){
HTTPClient http;
// Su nombre de dominio con la ruta del URL o la dirección IP
http.begin(serverName);
// Especifica content-type header
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
// Prepara el HTTP POST para solicitar dato
String httpRequestData="&pir="+ String(estado)+"";
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
}
