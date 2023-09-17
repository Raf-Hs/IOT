int led =22;
int boton= 19;
int valor = 0;
int estado = 0;
int valor_viejo = 0;

void setup(){
pinMode(led,OUTPUT);
pinMode(boton,INPUT);
}

void loop() {
valor= digitalRead(boton);
if ((valor_viejo == LOW) && (valor == HIGH)){
estado = 1-estado;
delay(10);
}
valor_viejo = valor;
if (estado==1){
digitalWrite(led, HIGH);
}
else{
digitalWrite(led,LOW);
}
}