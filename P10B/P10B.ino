#include <WiFi.h>
#include <DHT.h>

const char* ssid = "UTEQ-Alumnos";
const char* pass = "";
WiFiServer server(80);

#define DHTPIN 14          // El pin digital al que está conectado el DHT11
#define DHTTYPE DHT11      // Selecciona el tipo de sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(22, OUTPUT);  // LED1
  pinMode(19, OUTPUT);  // Relay
  pinMode(23, OUTPUT);  // LED 2 O MOTOR CON SU RELEY
  delay(10);
  Serial.println("Conectando");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.println();
  }
  Serial.println(WiFi.localIP());
  server.begin();
  dht.begin();  // Inicializar el sensor DHT11
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);

  float temperature = dht.readTemperature();  // Leer la temperatura en grados Celsius

  if (!isnan(temperature)) {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");

    if (temperature >= 24 && temperature <= 40) {
      digitalWrite(22, HIGH);  // Encender el tercer LED (pin 19)
    } else {
      digitalWrite(22, LOW);  // Apagar el tercer LED (pin 19)
    }
  }

  // Control del relé
  if (request.indexOf("/MN") != -1) {
    digitalWrite(23, HIGH);  // Encender el relé (pin 23)
  } else if (request.indexOf("/MFF") != -1) {
    digitalWrite(23, LOW);  // Apagar el relé (pin 23)
  }

 if (request.indexOf("/ON") != -1) {
    digitalWrite(19, HIGH);  // Encender el relé (pin 23)
  } else if (request.indexOf("/OFF") != -1) {
    digitalWrite(19, LOW);  // Apagar el relé (pin 23)
  }
  // Resto del código...

  client.println("HTTP/1.1 200 OK");
  client.println("<!DOCTYPE hmtl>");
  client.println("<html>");
  client.println("<head>");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div align='center'>");
  client.println("<h1>SERVIDOR WEB QUE CONTROLA DOS LEDS O DOS RELAY'S</h1>");
  client.println("<br/>");

  // Resto del código...

  client.println("<a href=\"/ON\">Encender Led</a><br/><br/>");
  client.println("<a href=\"/OFF\">Apagar Led</a><br/><br/>");
  client.println("<a href=\"/MN\">Encender Motor</a><br/><br/>");
  client.println("<a href=\"/MFF\">Apagar Motor</a><br/>");
  client.println("<a href=\"/MA\">Encender Motor</a><br/><br/>");
  client.println("<a href=\"/MB\">Apagar Motor</a><br/>");
  client.println("</div>");
  client.println("<hr/>");
  client.println("<br>");
  client.println("<div align='center'>");
  client.println("<h2>Grupo T207 se van a estadía!!!!</h2>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
  client.flush();
  delay(10);
}
