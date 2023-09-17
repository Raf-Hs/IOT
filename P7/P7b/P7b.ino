#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <Servo.h> //librería para el ESP32Servo.h
#include <FirebaseESP32.h>
#include <WiFi.h>
// Conexión al firestores y a la red
#define FIREBASE_HOST "https://grupot207aplicaciones-9fcc5-default-rtdb.firebaseio.com/" //nombre proyecto Firebase
#define FIREBASE_Authorization_key "QMnJNlbnp3V8b1oWdHLYg8QJbGsicnHUAe1c2XRH"
#define WIFI_SSID "UTEQ-Alumnos" // Modificar el nombre del proveedor de servicios internet
#define WIFI_PASSWORD "" // Modificar el password del Wifi
FirebaseData firebaseData;
FirebaseJson json;
#include <Adafruit_Sensor.h>
Servo myservo;
int servomotor=4; //GPIO 4 puerto digital del servo motor
int pos = 0;
const int pir=19;
const char* ssid = "UTEQ-Alumnos";
const char* password = "";

// ingresa tu número telefónico tal como te lo manda Whatsapp
String phoneNumber = "5214427477664";
// ingresa el apiKey que te llegó a tu celular
String apiKey = "9331869";

// método que permite enviar el mensaje por medio del Whatsapp.
void sendMessage(String mensaje){
// Dato o mensaje enviado por medio de este link

String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey
+ "&text=" + urlEncode(mensaje);
WiFiClient client;
HTTPClient http;
http.begin(client, url);
// se especifia el tipo de contenido de la cabecera
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
// enviar por el método HTTP POST
int httpResponseCode = http.POST(url);
if (httpResponseCode == 200){
Serial.print("El mensaje fue enviado exitosamente");
}
else{
Serial.println("Error enviando el mensaje");
Serial.print("HTTP response code: ");
Serial.println(httpResponseCode);
}
// cierra el cliente http.
http.end();
}
void setup() {
Serial.begin(9600);
WiFi.begin(ssid, password);
Serial.println("Connecting");
while(WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
myservo.attach(servomotor); //inicializa el puerto digital para el servo motor
pinMode(pir, INPUT);
}
Serial.println("");
Serial.print("Conectado a la red WiFi con la dirección IP:"); 
Serial.println(WiFi.localIP());
Serial.println();
Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
// Se envia el mensaje una vez al celular víael método sendMessage

}
void loop() {
  
  int sensor;
sensor=digitalRead(pir); //lectura del pir
if(sensor==HIGH){
Serial.print(" Presencia: ");
Firebase.setFloat(firebaseData, "/MiESP32/Presencia", 1);
sendMessage("Se abrio la puerta");
myservo.write(90);
delay(10000);
sendMessage("Se Cerro la puerta");
 myservo.write(0);
 delay(1000);
}else{
if(sensor==LOW){
Serial.print("No Presencia: ");
Firebase.setFloat(firebaseData, "/MiESP32/Presencia", 0);

 myservo.write(0);
delay(1000);
}
}
delay(100);

}
