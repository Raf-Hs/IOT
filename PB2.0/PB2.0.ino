#include <FirebaseESP32.h>
#include <WiFi.h>
// Conexión al firestores y a la red
#define FIREBASE_HOST "https://grupot207aplicaciones-9fcc5-default-rtdb.firebaseio.com/" //nombre proyecto Firebase
#define FIREBASE_Authorization_key "QMnJNlbnp3V8b1oWdHLYg8QJbGsicnHUAe1c2XRH"
#define WIFI_SSID "UTEQ-Alumnos" // Modificar el nombre del proveedor de servicios internet
#define WIFI_PASSWORD "" // Modificar el password del Wifi// Modificar el password del Wifi
FirebaseData firebaseData;
FirebaseJson json;

void setup() {
Serial.begin(9600);
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
float valor = 11.4;
Serial.print(" Sensor: ");
Serial.print(valor);

Serial.print("%");
Serial.println();
Firebase.setFloat(firebaseData, "/MiESP32/Sensor", valor);
delay(200);
}
