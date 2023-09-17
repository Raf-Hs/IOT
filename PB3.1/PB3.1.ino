#include <FirebaseESP32.h>
#include <WiFi.h>

#define FIREBASE_HOST "https://grupot207aplicaciones-9fcc5-default-rtdb.firebaseio.com/" //nombre proyecto Firebase
#define FIREBASE_Authorization_key "QMnJNlbnp3V8b1oWdHLYg8QJbGsicnHUAe1c2XRH"
#define WIFI_SSID "UTEQ-Alumnos" // Modificar el nombre del proveedor de servicios internet
#define WIFI_PASSWORD "" // Modificar el password del Wifi


FirebaseData firebaseData;
FirebaseJson json;
int estado;
int led=2; // led de puerto GPIO 2

#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); // dht(puerto, dispositivo) instancia de la
//clase DHT
const int relay=22;

void setup() {
Serial.begin(9600);
pinMode(relay,OUTPUT);
pinMode(led,OUTPUT);
WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
Serial.print("Connecting...");
while (WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(300);
}
Serial.println();

Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
Serial.println();
Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
}

void loop() {
int motor;
Firebase.getInt(firebaseData, "/MiESP32/MOTOR");
motor=firebaseData.intData();
Serial.println(motor);
delay(200);
if(motor ==1) {
digitalWrite(relay,HIGH);
delay(1000);
digitalWrite(relay,LOW);
delay(1000);
}else{
digitalWrite(relay,LOW);
}
delay(100);
}
