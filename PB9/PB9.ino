const int buzzer=4; // PUERTO GPIO 4 PARA EL PIN + DEL BUZZER.

void setup() {
pinMode(buzzer,OUTPUT); //Configurar el pin 4 como salida.
}

void loop() {
digitalWrite(buzzer, HIGH); //activar el buzzer y emitir sonido
delay(1000); //duración de un segundo
digitalWrite(buzzer, LOW); //desactivar el buzzer
delay(1000); // esperar un segundo

}
