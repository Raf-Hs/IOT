


#include <FirebaseESP32.h>
#include <WiFi.h>

#define FIREBASE_HOST "https://grupot207aplicaciones-9fcc5-default-rtdb.firebaseio.com/" //nombre proyecto Firebase
#define FIREBASE_AUTH "QMnJNlbnp3V8b1oWdHLYg8QJbGsicnHUAe1c2XRH"

const char* ssid = "UTEQ-Alumnos";  // Nombre de tu red Wi-Fi
const char* password = "";  // Contraseña de tu red Wi-Fi
const int trigPin = 5;  // GPIO 5 para el pin del disparador o Trigger
const int echoPin = 18;  // GPIO 18 para el pin del Echo o regreso del pulso
const int buzzer = 4;  // GPIO 4 para el pin del buzzer
const int redLedPin = 23;  // GPIO 2 para el pin del LED rojo
const int greenLedPin = 2;  // GPIO 3 para el pin del LED verde

long duracion_pulso;  // Variable que determina la duración del pulso que toma el Echo
float distancia;  // Variable que determina la distancia del objeto al sensor

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  delay(1000);  // Esperar un momento para la conexión del monitor serie

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);

  Serial.println("Conectando a la red Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conexión Wi-Fi establecida");

  Serial.println("Inicializando Firebase...");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase inicializado");
}

void loop() {
  // Medir la distancia con el sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion_pulso = pulseIn(echoPin, HIGH);
  distancia = (duracion_pulso) * (0.0343 / 2);

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Activar alarma y LEDs si la distancia es menor a 10 cm
  if (distancia < 10) {
    Serial.println("¡¡¡ALARMA!!! Distancia menor a 10 cm");
    digitalWrite(buzzer, HIGH);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);

Firebase.setInt(firebaseData, "/MiDHT11/distancia", distancia);
    // Subir la distancia a Firebase
  
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }

  delay(1000);
}
