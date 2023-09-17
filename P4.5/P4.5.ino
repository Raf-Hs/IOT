int led=22; // puerto digital GPIO22
int boton=19; // puerto digital GPIO19

void setup() {
Serial.begin(9600);
for(int i=21;i<=23;i++){
pinMode(i,OUTPUT);
}; // puerto 22 como salida del led
pinMode(boton,INPUT); // puerto 19 como entrada del boton 
}

void loop() {
int estado; // varible que guarda el estado de la lectura del puerto
estado=digitalRead(boton); //se le la entrada del boton
if(estado==HIGH){ // se puede comparar un High o 1
 for(int i=21;i<=23;i++){
digitalWrite(i,HIGH);
delay(500);
digitalWrite(i,LOW);
delay(500);
}
}else{
 for(int i=21;i<=23;i++){
digitalWrite(i,LOW);
delay(500);
}
}

}
