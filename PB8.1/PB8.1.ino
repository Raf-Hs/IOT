#include <SPI.h>
#include <Wire.h>
#include <FirebaseESP32.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>
#include <FS.h>
#include "DHT.h"

#define Largo_Pantalla 128 // Largo de la pantalla en pixeles
#define Ancho_Pantalla 32 // Ancho de la pantalla en pixeles
#define Reset_Oled 4 // pin 4 definido para borrar la pantalla
#define FIREBASE_HOST "https://grupot207aplicaciones-9fcc5-default-rtdb.firebaseio.com/" //nombre proyecto Firebase
#define FIREBASE_Authorization_key "QMnJNlbnp3V8b1oWdHLYg8QJbGsicnHUAe1c2XRH"
#define WIFI_SSID "UTEQ-Alumnos" // Modificar el nombre del proveedor de servicios internet
#define WIFI_PASSWORD "" // Modificar el password del Wifi
#define DHTPIN 4
#define DHTTYPE DHT11

Adafruit_SSD1306 display(Largo_Pantalla, Ancho_Pantalla, &Wire, Reset_Oled);
DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  Serial.begin(9600);


  Serial.println("Prueba DHT");
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Existe falla en el SSD1306"));
    while (1);
  }

  if (!SD.begin()) {
    Serial.println("Falla en la operación de la SD Card");
    return;
  }

  writeFile(SD, "/datos.txt", "Aqui va la información de los datos\r\n");

  display.clearDisplay();
  display.drawPixel(10, 30, SSD1306_WHITE);
  display.display();
  delay(2000);
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falla en la lectura del sensor, verifica librería y conexión"));
    return;
  }

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("°C");

  Firebase.setFloat(firebaseData, "/MiESP32/Humedad", h);
  Firebase.setFloat(firebaseData, "/MiESP32/Temperatura", t);

  String humedadData = String(h) + ",Humedad\r\n";
  Serial.println(humedadData);
  appendFile(SD, "/datos.txt", humedadData.c_str());

  String temperaturaData = String(t) + ",Temperatura\r\n";
  Serial.println(temperaturaData);
  appendFile(SD, "/datos.txt", temperaturaData.c_str());

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SS
