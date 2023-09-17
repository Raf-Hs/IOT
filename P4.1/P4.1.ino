int vector[]={21,22,23};

int boton= 19;
int valor = 0;
int estado = 0;
int valor_viejo = 0;

void setup(){
  Serial.begin(9600);
for(int i=0;i<3;i++){
pinMode(vector[i],OUTPUT);
}
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
for(int i=0;i<3;i++){
digitalWrite(vector[i],HIGH);

}}
else{
for(int i=0;i<3;i++){

digitalWrite(vector[i], LOW);


}
}
}
