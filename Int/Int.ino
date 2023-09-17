                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           #include <Servo.h>
#include <FirebaseESP32.h>
#include <WiFi.h>

#define FIREBASE_HOST "test-5583c-default-rtdb.firebaseio.com" // nombre del proyecto Firebase
#define FIREBASE_AUTHORIZATION_KEY "jatK68ymsbUuUHA6jaC6curaY8XQfe1g4VAYRgBA"
#define WIFI_SSID "UTEQ-Alumnos" // Nombre de la red WiFi
#define WIFI_PASSWORD "" // Contraseña de la red WiFi

FirebaseData firebaseData;
FirebaseJson json;

int ledAbierto = 23; // LED en el puerto GPIO 23
int ledCerrado = 22; // LED en el puerto GPIO 22

Servo myservo;
int servomotor = 4; // Puerto digital del servo motor (GPIO 4)
int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(servomotor);

  pinMode(ledAbierto, OUTPUT);
  pinMode(ledCerrado, OUTPUT);

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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTHORIZATION_KEY);
}

void loop() {
  int motor;
  if (Firebase.ready()) {
    Firebase.getInt(firebaseData, "/MiESP32/MOTOR");
    motor = firebaseData.intData();
    Serial.println(motor);
    delay(200);

    if (motor == 1) {
      Serial.println("Abierto");
      digitalWrite(ledAbierto, HIGH); // Enciende el LED correspondiente al estado "abierto"
      digitalWrite(ledCerrado, LOW); // Apaga el LED correspondiente al estado "cerrado"
      myservo.write(180);
      
    } else {
      Serial.println("Cerrado");
      digitalWrite(ledAbierto, LOW); // Apaga el LED correspondiente al estado "abierto"
      digitalWrite(ledCerrado, HIGH); // Enciende el LED correspondiente al estado "cerrado"
      myservo.write(0); // Mueve el servo motor a la posición final directamente

    }
  }
}
