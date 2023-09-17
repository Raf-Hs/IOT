#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define Largo_Pantalla 128 // Largo de la pantalla en pixeles
#define Ancho_Pantalla 32 // Ancho de la pantalla en pixeles
// Declaramos los parámetros para display SSD1306 conectado al I2C del ESP32 que son pines SDA (GPIO21)y SCL (GPIO 22)
#define Reset_Oled 4 // pin 4 definido para borrar la pantalla
Adafruit_SSD1306 display(Largo_Pantalla, Ancho_Pantalla, &Wire, Reset_Oled);

void setup() {
Serial.begin(9600);
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // direccion del display 0x3C para el OLED de 128x32
Serial.println(F("Existe falla en el SSD1306"));
for(;;); // si falla se marca un loop infinito
}
// Limpia el buffer
display.clearDisplay(); // clearDisplay() borra lo que está en el buffer y pantalla. //
//Dibuja un punto en la pantalla/
display.drawPixel(10,30, SSD1306_WHITE); // Muestra un pixel en la posición X=10 y Y=30
display.display();
delay(2000);
}
void loop() {
display.clearDisplay(); // Limpia en inicio la pantalla
display.setTextSize(1); // 1 es la escala normal
display.setTextColor(SSD1306_WHITE); // Escribe texto en azul sobre fondo negro
display.setCursor(10,0); // X=10 y Y=0
display.println(F("APLICACIONES IoT!"));
/* --------------------------------------------------------- */
display.setTextSize(2); // 2 escala más grande del texto
display.setTextColor(SSD1306_WHITE);
display.println(" DAM UTEQ");
/*------------------------------------------------------------*/
display.setTextSize(1); // método setTextSize(tamaño_texto)
display.setTextColor(SSD1306_WHITE); // INTERCAMBIANDO LOS COLORES
display.setCursor(25,25); // coordenadas (x,y) para localizar texto en pantalla
display.println("GRUPO T207"); //Este permite visualizar el dato en la pantalla.
display.display();
delay(3000);
//display.invertDisplay(true); // elimina los comentarios para ver otra forma de trabajar del display
//delay(1000); // elimina las barras al inicio para que veas la función
display.invertDisplay(false);
delay(1000);
}
