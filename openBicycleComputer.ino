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
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define XPOS 0
#define YPOS 1
#define DELTAY 2

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


unsigned long wheel = 2240; 
unsigned long constant;
unsigned long time;
unsigned long start;
char output[11];
int pushButton = 7;
boolean is_pushed, is_released;
int is_pushed_old;

void setup(void) {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    pinMode(pushButton, INPUT_PULLUP);
  display.display();
  delay(1000);
    display.clearDisplay();
  display.display();
  constant = get_constant();
  is_released = LOW;
    //Keyboard.begin();
}

  double abc = 0;
void loop() {
  
  
  int is_pushed = digitalRead(pushButton);
  int a_read = analogRead(pushButton);
  
  if (is_pushed_old != is_pushed) {
 //   Serial.println(a_read);
  }
  is_pushed_old = is_pushed;
  
  if (is_pushed == LOW) {
    is_released = HIGH;
  }
  else {
    if (is_released == HIGH) {
      is_released = LOW;
      /*
      Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE);
      Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE);
      Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE);
      Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE);
      if (abc>=10) {Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE);}
      if (abc>=100) {Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE);}
      if (abc>=1000) {Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE);}
      if (abc>=10000) {Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE);}
      */
      time = micros() - start;
      abc = get_mps(time);
//     String output_string;
//      dtostrf(abc,1,1,output);
//      output_string.toCharArray( output, 11);
      start = micros();
      Serial.println(abc);
//      Keyboard.print(abc);

  display.clearDisplay();
        display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(abc);
    display.display();

      delay(10);
      
    }
  }
}


double get_mps (unsigned long mic_sec) {
  return (double) constant / (double) mic_sec;
}

unsigned long get_constant () {
    
  return wheel * 3600 ;
}
