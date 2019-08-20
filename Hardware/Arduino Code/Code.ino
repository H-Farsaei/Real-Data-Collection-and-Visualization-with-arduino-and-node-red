//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
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

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//Light initializing
#define Light 3

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;

String temps ="";
String humid ="";


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.

  pinMode(Light, OUTPUT);
  digitalWrite(Light, LOW);
  
  Serial.begin(9600);
}


void loop() {
   // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }

  int tmp = (int)temperature;
  if (tmp>27){  
    analogWrite(Light, HIGH);
  } else {
    analogWrite(Light, LOW);
  }

  String str ="";  
  //  Serial.print("Sample OK: ");
  str += (int)temperature;
  str += " *C, ";
  str += (int)humidity;
  str += " %";
  str += "\n";
   Serial.print(str);
 
  
    // DHT11 sampling rate is 1HZ.
//    delay(2000);
  
  lcd.setCursor(0, 0);
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 // lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  temps = "   Temp  ";
  temps += (int)temperature;
  temps += " C"; 
  lcd.print(temps);
  
 // lcd.setCursor(0, 0);
//  lcd.print("humidity   ");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  humid = "   Humid ";
  humid += (int)humidity;
  humid += " %";
  lcd.print(humid);
  delay(2000);
}
