#include <SD.h> // incluir la librería SD(ESP32) SI NO NO FUNCIONA Y NO DETECTA LA SDCARD
#include <sd_defines.h> // LIBERIA SD CARD QUE DEFINE PUERTOS
#include <sd_diskio.h> // LECTURA DE LA INFORMACIÓN
#include <FS.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <SPI.h>
#define DBG_OUTPUT_PORT Serial
#ifndef STASSID
#define STASSID "UTEQ-Alumnos" // tu nombre de tu proveedor web

#define STAPSK "" // contraseña
#endif
const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "Mi_esp32"; // nombre del servidor web de la SDcard
WebServer server(80); // conectamos al servidor web por el puerto 80 para la petición.
static bool hasSD = false;
File uploadFile;

void returnOK() {
server.send(200, "text/plain", "");
}
void returnFail(String msg) {
server.send(500, "text/plain", msg + "\r\n");
}
bool loadFromSdCard(String path) {
String dataType = "text/plain";
if (path.endsWith("/")) {
path += "index.htm";
}
// extensiones a las que te puedes conectar
if (path.endsWith(".src")) {
path = path.substring(0, path.lastIndexOf("."));
} else if (path.endsWith(".htm")) {
dataType = "text/html";
} else if (path.endsWith(".css")) {
dataType = "text/css";
} else if (path.endsWith(".js")) {
dataType = "application/javascript";
} else if (path.endsWith(".png")) {
dataType = "image/png";
} else if (path.endsWith(".gif")) {
dataType = "image/gif";
} else if (path.endsWith(".jpg")) {
dataType = "image/jpeg";
} else if (path.endsWith(".ico")) {
dataType = "image/x-icon";
} else if (path.endsWith(".xml")) {
dataType = "text/xml";
} else if (path.endsWith(".pdf")) {
dataType = "application/pdf";
} else if (path.endsWith(".zip")) {
dataType = "application/zip";
}

File dataFile = SD.open(path.c_str());
if (dataFile.isDirectory()) {
path += "/index.htm"; //PAGINA INDEX.HTM QUE ES LA INDEX O INICIAL PARA LA PÁGINA WEB
dataType = "text/html";
dataFile = SD.open(path.c_str());
}
if (!dataFile) {
return false;
}
if (server.hasArg("download")) {
dataType = "application/octet-stream";
}
if (server.streamFile(dataFile, dataType) != dataFile.size()) {
DBG_OUTPUT_PORT.println("Se mandas mas datos de los esperado!");
}
dataFile.close();
return true;
}
void handleFileUpload() {
if (server.uri() != "/edit") {
return;
}
HTTPUpload& upload = server.upload();
if (upload.status == UPLOAD_FILE_START) {
if (SD.exists((char *)upload.filename.c_str())) {
SD.remove((char *)upload.filename.c_str());
}
uploadFile = SD.open(upload.filename.c_str(), FILE_WRITE);
DBG_OUTPUT_PORT.print("Upload: START, filename: ");
DBG_OUTPUT_PORT.println(upload.filename);
} else if (upload.status == UPLOAD_FILE_WRITE) {
if (uploadFile) {
uploadFile.write(upload.buf, upload.currentSize); }
DBG_OUTPUT_PORT.print("Upload: WRITE, Bytes: ");
DBG_OUTPUT_PORT.println(upload.currentSize); } else
if (upload.status == UPLOAD_FILE_END) { if (uploadFile)
{
uploadFile.close();
}
DBG_OUTPUT_PORT.print("Upload: END, Size: ");
DBG_OUTPUT_PORT.println(upload.totalSize);
}
}

void deleteRecursive(String path) {
File file = SD.open((char *)path.c_str());
if (!file.isDirectory()) {
file.close();
SD.remove((char *)path.c_str());
return;
}
file.rewindDirectory();
while (true) {
File entry = file.openNextFile();
if (!entry) {
break;
}
String entryPath = path + "/" + entry.name();
if (entry.isDirectory()) {
entry.close();
deleteRecursive(entryPath);
} else {
entry.close();
SD.remove((char *)entryPath.c_str());
}
yield();
}
SD.rmdir((char *)path.c_str());
file.close();
}
void handleDelete() {
if (server.args() == 0) {
return returnFail("BAD ARGS");
}
String path = server.arg(0);
if (path == "/" || !SD.exists((char *)path.c_str())) {
returnFail("BAD PATH");
return;
}
deleteRecursive(path);
returnOK();
}
void handleCreate() {
if (server.args() == 0) {
return returnFail("BAD ARGS");
}
String path = server.arg(0);
if (path == "/" || SD.exists((char *)path.c_str())) {
returnFail("BAD PATH");

return;
}
if (path.indexOf('.') > 0) {
File file = SD.open((char *)path.c_str(), FILE_WRITE);
if (file) {
// file.write((const char *)0);
file.close();
}
} else {
SD.mkdir((char *)path.c_str());
}
returnOK();
}
void printDirectory() {
if (!server.hasArg("dir")) {
return returnFail("BAD ARGS");
}
String path = server.arg("dir");
if (path != "/" && !SD.exists((char *)path.c_str())) {
return returnFail("BAD PATH");
}
File dir = SD.open((char *)path.c_str());
path = String();
if (!dir.isDirectory()) {
dir.close();
return returnFail("NOT DIR");
}
dir.rewindDirectory();
server.setContentLength(CONTENT_LENGTH_UNKNOWN);
server.send(200, "text/json", "");
WiFiClient client = server.client();
server.sendContent("[");
for (int cnt = 0; true; ++cnt) {
File entry = dir.openNextFile();
if (!entry) {
break;
}
String output;
if (cnt > 0) {
output = ',';
}
output += "{\"type\":\"";
output += (entry.isDirectory()) ? "dir" : "file";
output += "\",\"name\":\"";
output += entry.name();
output += "\"";

output += "}";
server.sendContent(output);
entry.close();
}
server.sendContent("]");
dir.close();
}
void handleNotFound() {
if (hasSD && loadFromSdCard(server.uri())) {
return;
}
String message = "SDCARD No detectada\n\n";
message += "URI: ";
message += server.uri();
message += "\nMethod: ";
message += (server.method() == HTTP_GET) ? "GET" : "POST";
message += "\nArguments: ";
message += server.args();
message += "\n";
for (uint8_t i = 0; i < server.args(); i++) {
message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n"; }
server.send(404, "text/plain", message);
DBG_OUTPUT_PORT.print(message);
}
void setup(void) {
DBG_OUTPUT_PORT.begin(115200);
DBG_OUTPUT_PORT.setDebugOutput(true);
DBG_OUTPUT_PORT.print("\n");
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
DBG_OUTPUT_PORT.print("Conectando a ");
DBG_OUTPUT_PORT.println(ssid);
// Se espera a la conexión del wifi
uint8_t i = 0;
while (WiFi.status() != WL_CONNECTED && i++ < 20) {//esperar 10 segundos
delay(500);
}
if (i == 21) {
DBG_OUTPUT_PORT.print("No te puedes conectar a");
DBG_OUTPUT_PORT.println(ssid);
while (1) {
delay(500);
}
}
DBG_OUTPUT_PORT.print("Conectado ! a la dirección IP: ");
DBG_OUTPUT_PORT.println(WiFi.localIP());

if (MDNS.begin(host)) {
MDNS.addService("http", "tcp", 80);
DBG_OUTPUT_PORT.println("el MDNS responde ");
DBG_OUTPUT_PORT.print("Ahora te puedes conectar a este servidor http://");
DBG_OUTPUT_PORT.print(host);
DBG_OUTPUT_PORT.println(".local");
}

server.on("/list", HTTP_GET, printDirectory);
server.on("/edit", HTTP_DELETE, handleDelete);
server.on("/edit", HTTP_PUT, handleCreate);
server.on("/edit", HTTP_POST, []() {
returnOK();
}, handleFileUpload);
server.onNotFound(handleNotFound);
server.begin();
DBG_OUTPUT_PORT.println("HTTP servidor inicializado");
if(SD.begin(5)) { // puerto GPIO5 (D5)Cdel ESP32 para que iniciar la SD.
DBG_OUTPUT_PORT.println(" SD inicializada");
hasSD = true;
}
}
void loop(void) {
server.handleClient();
// MDNS.update();
}
