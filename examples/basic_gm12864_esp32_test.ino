#include <Arduino.h>
#include <Wire.h>
#include <Lcd_st7567s.h>
#include <Smile.c>

Lcd_st7567s lcd;

void setup() {
  lcd.init();
}

void loop() {
  
  /* tests*/
  lcd.displayPicture(&smile[0], 64);
  delay(3000);
  
  lcd.testPixel(2);  
  
  lcd.clear(false);
  lcd.cursor(7, 0);                    //Character display position. y=0-3, x=0-17
  lcd.display("Test");   
  lcd.cursor(0, 2);
  lcd.display("ABCDEFGHIJKLMNOPQR");
  lcd.cursor(0, 3);
  lcd.display("1234567890+-*/<>=$");
  lcd.cursor(0, 4);
  lcd.display("%^&(){}:;'|?,.~\\[]");
  lcd.cursor(0, 5);
  lcd.display("ABCDEFGHIJKLMNOPQR");
  lcd.cursor(0, 6);
  lcd.display("123456789+-*/<>=$@");
  lcd.cursor(0, 7);
  lcd.display("%^&(){}:;'|?,.~\\[]");
  delay(3000);
  lcd.clear(false);
}
