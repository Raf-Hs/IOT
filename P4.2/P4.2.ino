/*int led1 =22;
int led2 =23;
int led3 =21;
int boton= 19;
int valor = 0;
int estado = 0;
int valor_viejo = 0;

void setup(){
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
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
  
digitalWrite(led1,HIGH);
delay(1000);


digitalWrite(led2,HIGH);
delay(1000);


digitalWrite(led3,HIGH);
delay(1000);


}
else{
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
}
}
*/

int led =22;
int led2 =23;
int led3 =21;
int boton= 19;
int valor = 0;
int estado = 0;
int valor_viejo = 0;

void setup(){
for(int i=21;i<=23;i++){
pinMode(i,OUTPUT);
}
pinMode(boton,INPUT);
}

void loop() {
valor= digitalRead(boton);
if ((valor_viejo == LOW) && (valor == HIGH)){
estado = 1-estado;

}
valor_viejo = valor;
if (estado==1){

  for(int i=21;i<=23;i++){
digitalWrite(i,HIGH);
delay(500);
digitalWrite(i,LOW);
delay(500);
}


 
}
else{


  for(int i=21;i<=23;i++){

digitalWrite(i,LOW);
delay(500);
}


}
}
