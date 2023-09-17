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
void setup() {
Serial.begin(9600);
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
String let;
Firebase.getInt(firebaseData, "/MiESP32/ESTADO");
estado=firebaseData.intData();
Firebase.getString(firebaseData, "/MiESP32/CADENA");
let=firebaseData.stringData();
Serial.println(let);
Serial.println("ESTADO= " + String(firebaseData.intData()));
delay(200);
if(estado ==1) {
digitalWrite(led,HIGH);
}else{
digitalWrite(led,LOW);
}
delay(100);
}
