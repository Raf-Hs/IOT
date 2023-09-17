int arreglo[]={21,22,23};
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
for(int i=2; i>-1;i--){
pinMode(arreglo[i],OUTPUT);
}
}

void loop() {
for(int  i=2; i>-1;i--){
digitalWrite(arreglo[i], HIGH);
delay(1000);

digitalWrite(arreglo[i],LOW);
delay(1000);
}
}
