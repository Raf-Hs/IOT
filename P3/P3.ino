int const led1=19;
int const led2=21;
int const led3=22;
int const led4=23;
int leds[4]={led1, led2, led3, led4};

void setup(){
  Serial.begin(9600);
    for(int i=0; i<4; i++){
                            pinMode(leds[i], OUTPUT);
                          }
}

void loop(){
  char opcion; 
    if(Serial.available()>0){
      opcion=Serial.read();
      switch(opcion){
              case '1':
              uno();
              break;
              case '2':
              dos();
              break;
                case '3':
               tres();
              break;
                case '4':
              cuatro();
              break;
      }
  }
}

void uno(){
                digitalWrite(led1, 1);
              delay(1000);
              digitalWrite(led1, 0);
              delay(1000);
              digitalWrite(led4, 1);
              delay(1000);
              digitalWrite(led4, 0);
              delay(1000);
              digitalWrite(led3, 1);
              delay(1000);
              digitalWrite(led3, 0);
              delay(1000);
              digitalWrite(led2, 1);
              delay(1000);
              digitalWrite(led2, 0);
              delay(1000);
            

}
void dos(){
  digitalWrite(led2, 1);
              delay(1000);
              digitalWrite(led2, 0);
              delay(1000);
              digitalWrite(led3, 1);
              delay(1000);
              digitalWrite(led3, 0);
              delay(1000);
              digitalWrite(led4, 1);
              delay(1000);
              digitalWrite(led4, 0);
              delay(1000);
              digitalWrite(led1, 1);
              delay(1000);
              digitalWrite(led1, 0);
              delay(1000);

}
void tres(){
  digitalWrite(led1, 1);
              delay(1000);
              digitalWrite(led1, 0);
              delay(1000);
              digitalWrite(led3, 1);
              delay(1000);
              digitalWrite(led3, 0);
              delay(1000);

}
void cuatro(){

               digitalWrite(led4, 1);
              delay(1000);
              digitalWrite(led4, 0);
              delay(1000);
              digitalWrite(led2, 1);
              delay(1000);
              digitalWrite(led2, 0);
              delay(1000);

}