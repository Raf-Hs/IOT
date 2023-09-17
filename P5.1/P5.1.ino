#include <TinyGPS++.h> //La librería la puedes encontrar como TinyGPS++ o TinyGPSPlus
#include <SoftwareSerial.h>
#include <FirebaseESP32.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>

#define FIREBASE_HOST "https://grupot207aplicaciones-9fcc5-default-rtdb.firebaseio.com/" //nombre proyecto Firebase
#define FIREBASE_Authorization_key "QMnJNlbnp3V8b1oWdHLYg8QJbGsicnHUAe1c2XRH"
#define WIFI_SSID "MEGACABLE-2.4G-32A5" // Modificar el nombre del proveedor de servicios internet
#define WIFI_PASSWORD "2S7xDhn38u" // Modificar el password del Wifi
FirebaseData firebaseData;
FirebaseJson json;

static const int RXPin = 16, TXPin =17;// Rx=16 y Tx=17 pines del ESP32
static const uint32_t GPSBaud = 9600; // La velocidad de transmisión del GPS es 9600 baudios
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup(){
Serial.begin(9600); // velocidad de comunicación con el monitor serial
ss.begin(GPSBaud);
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
Serial.println("Calando tu ubicacion😜👌");
Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);

 // inicializa la comunicación con el gps
}
void loop(){
float lat = gps.location.lat(); // Método readHumedity() para obtener la
//humedad //ambiente
float lng = gps.location.lng();
while (ss.available() > 0) // mientras lo que se reciba sea mayor a cxvero
if (gps.encode(ss.read())){ //si el metodo encode decodifica la lectura que se hace del método read()
Serial.print(F("Location: "));
if (gps.location.isValid()){ // si location.isValid() se encuentran los valores de localización
Serial.print(gps.location.lat(), 6); // se imprime la latitud con 6 digitos
Serial.print(F(",")); // se imprime una coma
Serial.print(gps.location.lng(), 6); //se imprime la longitud con 6 digitos
}else{
Serial.print(F("Inválido")); // en caso de no tener los datos de localización se indica inválido.
}
Serial.print(F(" Fecha "));
if (gps.date.isValid()){ // se imprime fecha
Serial.print(gps.date.month()); // mes
Serial.print(F("/"));
Serial.print(gps.date.day()); // dia
Serial.print(F("/"));
Serial.print(gps.date.year());
Firebase.setFloat(firebaseData, "/MiDHT11/latitud", lat);
Firebase.setFloat(firebaseData, "/MiDHT11/longitud", lng); //año
}else{
Serial.print(F("Invalido")); // en caso contrario se imprime fecha inválida.
}
Serial.println();
}
if (millis() > 5000 && gps.charsProcessed() < 10) { // enc aso que no se detecte y no se procesan
//caracteres o sen menor de 10 se imprime que no se detecta el gps y que verifiques las conexiones rx y
//tx.
Serial.println(F("GPS no detectado: checa las conexiones rx y tx.")); while(true); // se hace un loop infinito
//para que el gps modifique el objeto mientras se mueve.
}
}
