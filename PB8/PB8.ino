#include <SD.h> //Librería propia para la micro SD Card
#include <SPI.h> // Protocolo de comunicación Serial Peripheral Interface
#include <FS.h> // Librería del File System que se encuentra en la librería propia de Arduino
void setup(){
Serial.begin(9600);
if(!SD.begin()){ // si no se inicializa la SD Card se manda un mensaje de Falla, en caso contrario
// se escriben los datos en el archivo.
Serial.println("Falla en la operación de la SD Card");
return; // retorna valor falso debido al fallo.
}
writeFile(SD, "/datos.txt", "Aqui va la información de los datos\r\n"); // función que sólo escribe una vez en el archivo
}
void loop(){
float temp =9.9; // valor de temperatura que escribe y que puede ser sustituido por el valor del sensor DHT11 u otro. 
String CadenaTotal=""; // se crea una variable de tipo cadena vacía para recibiir los datos concatenados 
String mensaje="Vaya con el clima!!!";
CadenaTotal=String(temp)+","+mensaje+"\r\n"; // se concatenan los datos para mandarlos al archivo
Serial.println(CadenaTotal);
appendFile(SD, "/datos.txt", CadenaTotal.c_str()); // se manda a la SD al archivo datos.txt la cadena CadenaTotal 
delay(5000);
}
/*-----------------------------Método para Escribir una sola vez FileWrite-------------------*/
void writeFile(fs::FS &fs, const char * path, const char * message){
Serial.printf("Escribiendo al Archivo: %s\n", path);
File file = fs.open(path, FILE_WRITE);
if(!file){
Serial.println("Falla al abrir el archivo para escribir");
return;
}
if(file.print(message)){
Serial.println("Escritura en el Archivo");
} else {
Serial.println("Falla de Escritura");
}
file.close();
}
/*---------------------Método para Agregar varios datos a un Archivo (appendFile())---------------*/
void appendFile(fs::FS &fs, const char * path, const char * message){
Serial.printf("Appending (agregando al) Archivo: %s\n", path);
File file = fs.open(path, FILE_APPEND);
if(!file){
Serial.println("Falla al abrir el archivo para agregar datos(appending)");
return;

}
if(file.print(message)){
Serial.println("Mensaje o datos agregados");
} else {
Serial.println("Falla al agregar datos");
}
file.close();
}
/*----Existen otros métodos que se pueden agregar para borrar archivos, crear directorio,
etc---*/ /*----Estos métodos se encuentran en el ejemplo que se encuentra en SD(esp32)
------------*/
