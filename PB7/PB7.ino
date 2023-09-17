#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* ssid = "INFINITUMxxxxxxx";
const char* password = "xxxxxxxxxxx";

// ingresa tu número telefónico tal como te lo manda Whatsapp
String phoneNumber = "521442xxxxxxx";
// ingresa el apiKey que te llegó a tu celular
String apiKey = "xxxxxxx";

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
Serial.begin(115200);
WiFi.begin(ssid, password);
Serial.println("Connecting");
while(WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Conectado a la red WiFi con la dirección IP:"); Serial.println(WiFi.localIP());
// Se envia el mensaje una vez al celular víael método sendMessage
sendMessage("Hola Grupo");
}
void loop() {
}
