#include <SPI.h>
#include <Wire.h>
#include <FirebaseESP32.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define Largo_Pantalla 128 // Largo de la pantalla en pixeles
#define Ancho_Pantalla 32 // Ancho de la pantalla en pixeles
// Declaramos los parámetros para display SSD1306 conectado al I2C del ESP32 que son pines SDA (GPIO21)y SCL (GPIO 22)
#define Reset_Oled 4 // pin 4 definido para borrar la pantalla
#define FIREBASE_HOST "https://grupot207aplicaciones-9fcc5-default-rtdb.firebaseio.com/" //nombre proyecto Firebase
#define FIREBASE_Authorization_key "QMnJNlbnp3V8b1oWdHLYg8QJbGsicnHUAe1c2XRH"
#define WIFI_SSID "UTEQ-Alumnos" // Modificar el nombre del proveedor de servicios internet
#define WIFI_PASSWORD "" // Modificar el password del Wifi
FirebaseData firebaseData;
FirebaseJson json;
#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
Adafruit_SSD1306 display(Largo_Pantalla, Ancho_Pantalla, &Wire, Reset_Oled);
DHT dht(DHTPIN, DHTTYPE); // dht(puerto, dispositivo) instancia de la
//clase DHT
const int relay=22;
void setup() {
Serial.begin(9600);

pinMode(relay,OUTPUT); // puerto GPIO digital que va al Sorce //del Relay
Serial.println("Prueba DHT");
dht.begin(); // inicializa el sensor.
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

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // direccion del display 0x3C para el OLED de 128x32
Serial.println(F("Existe falla en el SSD1306"));
for(;;); // si falla se marca un loop infinito



}
// Limpia el buffer
display.clearDisplay(); // clearDisplay() borra lo que está en el buffer y pantalla. //
//Dibuja un punto en la pantalla/
display.drawPixel(10,30, SSD1306_WHITE); // Muestra un pixel en la posición X=10 y Y=30
display.display();
delay(2000);
}
void loop() {
  delay(2000); //requiere de dos segundos para realizar la lectura. 
  float h= dht.readHumidity(); // Método readHumedity() para obtener la
//humedad //ambiente
float t = dht.readTemperature(); // Método readTemperature() obtiene la
//temperatura
if(isnan(h) || isnan(t)) { // isnan() verifica que lleguen los dos valores
Serial.println(F("Falla en la lectura del sensor, verifica librería y conexión"));
return;
}
Serial.print(" Humedad: ");
Serial.print(h); //se imprime la temperatura en el serial
Serial.println("%");
Serial.print(" Temepratura: ");
Serial.print(t); //se imprime la temperatura en el serial
Serial.println("°C");

Serial.println();
Firebase.setFloat(firebaseData, "/MiESP32/Humedad", h);
Firebase.setFloat(firebaseData, "/MiESP32/Temperatura", t);
delay(200);
display.clearDisplay(); // Limpia en inicio la pantalla
display.setTextSize(1); // 1 es la escala normal
display.setTextColor(SSD1306_WHITE); // Escribe texto en azul sobre fondo negro
display.setCursor(10,0); // X=10 y Y=0
display.println(F("APLICACIONES IoT!"));
/* --------------------------------------------------------- */
display.setTextSize(2); // 2 escala más grande del texto
display.setTextColor(SSD1306_WHITE);
display.println(h);
/*------------------------------------------------------------*/
display.setTextSize(1); // método setTextSize(tamaño_texto)
display.setTextColor(SSD1306_WHITE); // INTERCAMBIANDO LOS COLORES
display.setCursor(25,25); // coordenadas (x,y) para localizar texto en pantalla
display.println( t); //Este permite visualizar el dato en la pantalla.
display.display();
delay(3000);
//display.invertDisplay(true); // elimina los comentarios para ver otra forma de trabajar del display
//delay(1000); // elimina las barras al inicio para que veas la función
display.invertDisplay(false);
delay(1000);
}
