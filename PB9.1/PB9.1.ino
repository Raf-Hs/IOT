const int trigPin = 5; // GPIO 5 para el pin del disparador o Trigger
const int echoPin = 18; // GPIO 18 para el pin del Echo o regreso del pulso
long duracion_pulso; //variable que determina la duración del pulso que toma el Echo
float distancia; // variable de determina la distancia del objeto al sensor.
void setup() {
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
void loop() {
digitalWrite(trigPin, LOW); //no dispara por dos segundos
delayMicroseconds(2);
digitalWrite(trigPin, HIGH); // se dispara un señal por 10 microsegundos
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duracion_pulso = pulseIn(echoPin, HIGH); //función que toma la duración del pulso de la onda de retorno
distancia = (duracion_pulso) * (0.0343/2); // velocidad del sonido 0.0343 en cm o 343 m/s
Serial.print("Distancia objeto en cm): ");
Serial.println(distancia);
delay(1000);
}
