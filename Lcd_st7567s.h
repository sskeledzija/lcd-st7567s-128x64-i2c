/******************************
 * original code from
 * URL: https://github.com/mworkfun/ST7567A_128X32DOT_LCD
 * and 
 * URL: https://github.com/luetee/ST7567S_128X64_I2C
 *  
 * Modify for LCD ST7567S 128x64
 * screen:
 * x-----------------------> +
 * y                    |
 * |                    |
 * |---------------------
 * | 
 * v +
 *  
 ******************************/
#ifndef LCD_ST7567S_h
#define LCD_ST7567S_h

#include <Arduino.h>
#include <Wire.h>

#define DRAW_UPPER_RIGHT 0x01
#define DRAW_UPPER_LEFT  0x02
#define DRAW_LOWER_LEFT 0x04
#define DRAW_LOWER_RIGHT  0x08
#define DRAW_ALL (DRAW_UPPER_RIGHT|DRAW_UPPER_LEFT|DRAW_LOWER_RIGHT|DRAW_LOWER_LEFT)

class Lcd_st7567s{
  public:
    // LCD is driven by ST7567A IC.
    // Define instructions on page 37 of the ST7567A data sheet.
    enum ST7567A_C {
      displayON  = 0xaf,  //display on.
      displayOFF = 0xae,  //display off.
      
      startLine  = 0x40,  //Set display start line.
      restart    = 0xe2,  //restart command.
      seg        = 0xa0,  //Set scan direction of SEG, SEG = 1-0-1-0-0-0-0-MX; 
                          //MX=1-->reverse direction, MX=0-->normal direction.

      INV_normal = 0xa6,  //normal display.
      AP_normal  = 0xa4,  //normal display.
      
      BS         = 0xa3,  //select bias setting, bias = 1-0-1-0-0-0-1-BS, BS(0)=1/9,  BS(1)=1/7(at 1/65 duty).
      com        = 0xc8,  //Set output direction of COM, COM = 1-1-0-0-MY-X-X-X;
                          //MY=1-->reverse direction, MY=0-->normal direction.
                          
      powerCon1  = 0x2c,  //Controls the built-in power circuits;
      powerCon2  = 0x2e,  //Define instructions on page 43 of the ST7567A data sheet.
      powerCon3  = 0x2f,

      /********Adjust display brightness********/
      regRatio   = 0x22,  //Controls the regulation ratio of the built-in regulator;
                          //Define instructions on page 43 of the ST7567A data sheet.
      EV1        = 0x81,  //Define instructions on page 44 of the ST7567A data sheet.
      EV2        = 0x30,  

      /**********entension command set**********/
      exit_EC    = 0xfe,  //exit extension command set.
      enter_EC   = 0xff,  //enter extension command set.

      DSM_ON     = 0x72,  //display setting mode on.
      DSM_OFF    = 0x70,  //display setting mode off.
      DT         = 0xd6,  //set the display duty, DT=33.
      BA         = 0x90,  //BA=1/9, selects LCD bias ratio for the internal voltage follower to drive the LCD. 
                          //This command has priority over the Bias Select (BS).
      FR         = 0x9d,  //specifies the frame rate for duty.

      RMW        = 0xe0,  //Read-modify-Write command on page 42 of ST7567A datasheet.
      END        = 0xee,
    };
    
    Lcd_st7567s();
    void writeByteCommand(int dat);      //Write a command to LCD.
    void writeContCommand(int str[]);    //Continuously write commands to LCD.
    void init();                          //This initialization function is called when using LCD.
    void testPixel(int t);                //use to test LCD screen.
    
    void writeByteDat(int dat);          //Write a data to RAM.
    void writeContDat(int str[]);        //Continuously write data to RAM.
    int  readByteDat(int col, int page); //read one byte RAM data to MCU. col=0-127, page=0-3
    void displayPixel(int x,int y);       //display one pixel. X=0-31, Y=0-127
    void clearPixel(int x,int y);         //Does not display a pixel. X=0-31, Y=0-127 
    void clear(bool invcolor);            // false = RAM write '0', all pixels turn off. 
    void fontSize(int num);               //reserve
    void cursor(int x, int y);             //Character display position. x=0-17, y=0-3
    void displayPicture(const unsigned char picture [], int widthInPixels = 128); //display picture.
    void writeFont(int num);              //Writes the data from the font.c file to RAM.
    void display(char *str);              //4 lines of 18 characters each.        
    // import from U8G2 
    // https://github.com/olikraus/u8g2
    void drawLine(int x1, int y1, int x2, int y2, bool invcolor);
    void drawCircleSection(int x, int y, int x0, int y0, int option, bool invcolor, bool solid);
    void drawCircle(int x0, int y0, int rad, int option, bool invcolor, bool solid);
  private:
    int addr = 0x3f;  //Address of LCD device.
    int cursorInit[2]={0,0};
};

#endif
