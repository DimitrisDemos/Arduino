/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
#define pinBotoes 36

#define pinRs 13
#define pinEn 12
#define pinD4 14
#define pinD5 27
#define pinD6 26
#define pinD7 25
LiquidCrystal lcd(pinRs, pinEn, pinD4, pinD5, pinD6, pinD7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

}


void loop() {

    // Print a message to the LCD.
  LcdPrint("hello, world!");

  LcdPrint("hello, world!!!!!!!!!!!!!!!!!!");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
}

void LcdPrint(char *myString){
  int size = strlen(myString);
  lcd.setCursor(0, 0);
 
  if ( size > 16){
    lcd.setCursor(15, 0);
    lcd.print(myString);
    for (int positionCounter = 0; positionCounter < size; positionCounter++) {
      // scroll one position left:
      lcd.scrollDisplayLeft();
      // wait a bit:
      delay(300);
    }
  }
  else
  {
    lcd.print(myString);
  }
  delay(1000);
  lcd.clear();
}


