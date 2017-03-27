/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
DIN PINOUT to Digital Input
1 = D6
2 = D5
3 = D4
4 = D3
5 = D2
6 = D7
7 = D8
8 = GND
9 = D9


*********************************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET A4
Adafruit_SSD1306 display(OLED_RESET);     
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
int sensorVal=0;
//Sega
int pin1 = 6;//Up/Z
int pin2 = 5;//Down/Y
int pin3 = 4;//Left/X
int pin4 = 3;//Right/Mode
int pin5 = 2;//+5V
int pin6 = 7;//B/A
int pin7 = 8;//Select
int pin9 = 9;//C/Start
//GND is 8 for Genesis and 

int ledPin =  13;      
int pin1m = 0;      
int pin2m = 0;
int pin3m = 0;
int pin4m = 4;
int pin5m = 0;
int pin6m = 0;
int pin7m = 0;
int pin9m = 0;
int sum = 0;
void setup()   {                
  Serial.begin(250000);
  pinMode(pin1, INPUT_PULLUP);     
  pinMode(pin2, INPUT_PULLUP);  
  pinMode(pin3, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin5, INPUT_PULLUP);
  pinMode(pin6, INPUT_PULLUP);
  pinMode(pin7, OUTPUT);
  pinMode(pin9, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  //digitalWrite(5, HIGH);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //display.display();
  //delay(2000);
  // Clear the buffer.
  display.clearDisplay();
}
void loop() {
checkswitch();
  display.display();
  display.clearDisplay();
}
void check(){
   display.setTextSize(4);
   display.setTextColor(WHITE);
   pin1m = digitalRead(pin1);
   pin2m = digitalRead(pin2);
   pin3m = digitalRead(pin3);
   pin4m = digitalRead(pin4);
   pin5m = digitalRead(pin5);
   pin6m = digitalRead(pin6);
   pin7m = digitalRead(pin7);
   pin9m = digitalRead(pin9);
   
if (pin7m == HIGH) {//sega case
  
//if (pin1m == LOW) {
//display.print("u");
 //   sum+=1;
 // }
if (pin2m == LOW) {

display.print("->");
    sum+=2;
  }
if (pin3m == LOW) {
display.print("<-");
    sum+=4;
 }
if (pin4m == LOW) {
display.print("v");
    sum+=8;
  }
 if (pin5m == LOW) {
display.print("^");
    sum+=64;
  }
if (pin6m == LOW) {
display.print("B");
    sum+=16;
  }
if (pin9m == LOW) {
display.print("C");
    sum+=32;
  }
}
else if (pin7m == LOW) {
  if (pin1m == LOW ) {
    {
display.print("A");
    sum+=256;
  }
  }
if (pin6m == LOW ) {
display.print("A");
    sum+=512;
  }
if (pin9m == LOW) {
display.print("ST");
    sum+=128;
  }
}
}
void checkswitch(){
  sensorVal = digitalRead(11);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
switch(sensorVal)
        {
        case 0:display.println("Joystick");
          digitalWrite(pin7, HIGH);
          check();
          Serial.println(sum, DEC);
          sum=0;
          break;
        case 1:display.println("Sega");
          digitalWrite(pin7, LOW);
          check();
          digitalWrite(pin7, HIGH);
          delay(10);
          check();
          Serial.println(sum, DEC);
           sum=0;
            break;
        default:
            display.print("Joystick");
        }
}

