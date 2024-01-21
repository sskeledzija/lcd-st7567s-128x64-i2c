#include <Lcd_st7567s.h>
#include <Arduino.h>
#include <Wire.h>
#include <font.c>

/* LCD is driven by ST7567A IC.
 * Define instructions on page 37 of the ST7567A data sheet.
 */
Lcd_st7567s::Lcd_st7567s(){
  
}

/******************************************
 * Write a command to LCD.
 * Define instructions on page 23 of the ST7567A data sheet.
*******************************************/
void Lcd_st7567s::writeByteCommand(int dat){
  Wire.beginTransmission(addr);      // transmit to device 0x3f
  Wire.write(0x00);                  // Co=0,A0=0. data= Co-A0-0-0-0-0-0-0. 
  Wire.write(dat);                   // sends restart command. 
  Wire.endTransmission();            // stop transmitting
}

/******************************************
 * Init the LCD.
 * This initialization function is called when using LCD.
*******************************************/
void Lcd_st7567s::init(){
  Wire.begin();
  delay(10);

    writeByteCommand(0xE2);    //Internal reset
    delay(10);
    writeByteCommand(0xA2);    //0xa2 LCD bias ratio is 1/9; 0xa3 is bias ratio 1/7; 128X64=1/9
    
    //// normal screen
    writeByteCommand(0xA0);    //(0xa0-0xa1 is ADC direction selection) 0xa0 is segment forward, 0xa1 is segment reverse
    writeByteCommand(0xC8);    //com output mode drive direction is reverse
		//// flip screen
    //writeByteCommand(0xA1);    // may be bug, loss first 4 bits in each row
    //writeByteCommand(0xC0);
    
    //writeByteCommand(0xA7);    // 0xA6 Normal, 0xA7 Inverse

    //********Adjust display brightness********
    writeByteCommand(0x25);    //0x20-0x27 is the internal Rb/Ra resistance adjustment setting of V5 voltage RR=4.5V
    //writeByteCommand(0x24);    // only 0x25 and 0x24 is ok 
    writeByteCommand(0x81);    //Electricity Mode Settings
    writeByteCommand(0x20);
    
    writeByteCommand(0x2C);    //Internal Power Supply Control Mode
    writeByteCommand(0x2E);
    writeByteCommand(0x2F);
    clear(false);                        //initalize DDRAM

    writeByteCommand(0xAF);    
    writeByteCommand(0x40);

}

/******************************************
 * Used to test screen pixels.
*******************************************/
void Lcd_st7567s::testPixel(int t){
  for(int x=0; x<8; x++){
    writeByteCommand(0xb0 + x);  //y, page address y=1-0-1-1-y3-y2-y1-y0, 1-page with 8-rows

    /*******automatically increased by one******/
    writeByteCommand(0x10);      //x, column address x=0-0-0-0-1-x7-x6-x5-x4
    writeByteCommand(0x00);      //x, column address x=0-0-0-0-0-x3-x2-x1-x0
    
    for(int i=0; i<128; i++){
      writeByteDat(0xff);        //row=bit0--bit7, display on
      delay(t);
      }  
  }
  for(int x=0; x<8; x++){
    writeByteCommand(0xb0 + x);
    writeByteCommand(0x00);
    writeByteCommand(0x10);
    for(int i=0; i<128; i++){
      writeByteDat(0x00);       //row=bit0--bit7, display off
      delay(t);
      }  
  }
}

/******************************************
 * Write a data to LCD.
 * Define instructions on page 23 of the ST7567A data sheet.
*******************************************/
void Lcd_st7567s::writeByteDat(int dat){
  Wire.beginTransmission(addr);      // transmit to device 0x3f
  Wire.write(0x40);                  // Co=0,A0=1. data= Co-A0-0-0-0-0-0-0. 
  Wire.write(dat);                   // sends data. 
  Wire.endTransmission();            // stop transmitting
}

/******************************************
 * Continuously write data to LCD.
 * Define instructions on page 23 of the ST7567A data sheet.
*******************************************/
void Lcd_st7567s::writeContDat(int str[]){
  int len = 0;
  len = sizeof(str);
  Wire.beginTransmission(addr);      // transmit to device 0x3f
  for(int i=0; i<len-1; i++){
    Wire.write(0xc0);                // Co=1,A0=1. data= Co-A0-0-0-0-0-0-0. 
    Wire.write(str[i]);              // sends command.
  }
  Wire.write(0x40);                  // Co=0,A0=1. data= Co-A0-0-0-0-0-0-0. 
  Wire.write(str[len-1]);            // sends command.
  Wire.endTransmission();            // stop transmitting
}

/******************************************
 * read one byte RAM data to MCU.
 * Define instructions on page 23 of the ST7567A data sheet.
*******************************************/
int Lcd_st7567s::readByteDat(int col, int page){
  int dat;
  writeByteCommand(0xb0 + page);     //y, page address y=1-0-1-1-y3-y2-y1-y0, 1-page with 8-rows 
  writeByteCommand(0x10 + col/16);   //x, column address x=0-0-0-0-1-x7-x6-x5-x4
  writeByteCommand(col%16);          //x, column address x=0-0-0-0-0-x3-x2-x1-x0 

  for(int i=0; i<2; i++){
    Wire.requestFrom(addr, 2);       //request 2 bytes from slave device
    while(Wire.available()){         //slave may send less than requested
      dat = Wire.read();             //receive a byte as character
    }
  }
  return dat;
}

/******************************************
 * display one pixel. Read-modify-Write command on page 42 of ST7567A datasheet.
 * x=0-128, y=0-31
*******************************************/
void Lcd_st7567s::displayPixel(int x,int y){
  int dat;
  writeByteCommand(0xb0 + y/8);     //y, page address y=1-0-1-1-y3-y2-y1-y0, 1-page with 8-rows 
  writeByteCommand(0x10 + x/16);    //x, column address x=0-0-0-0-1-x7-x6-x5-x4
  writeByteCommand(x%16);           //x, column address x=0-0-0-0-0-x3-x2-x1-x0 
  
  writeByteCommand(RMW);            //start Read-modify-Write
  for(int i=0; i<2; i++){
    Wire.requestFrom(addr, 2);       //request 2 bytes from slave device
    while(Wire.available()){         //slave may send less than requested
      dat = Wire.read();             //receive a byte as character
    }
  }
  dat = (dat | (1<<(y%8)));
  writeByteDat(dat);                //row=bit0--bit7
  writeByteCommand(END);            //end Read-modify-Write
}

/******************************************
 * Does not display a pixel. Read-modify-Write command on page 42 of ST7567A datasheet.
 * x=0-128, y=0-31
*******************************************/
void Lcd_st7567s::clearPixel(int x,int y){
  int dat;
  writeByteCommand(0xb0 + y/8);     //y, page address y=1-0-1-1-y3-y2-y1-y0, 1-page with 8-rows 
  writeByteCommand(0x10 + x/16);    //x, column address x=0-0-0-0-1-x7-x6-x5-x4
  writeByteCommand(x%16);           //x, column address x=0-0-0-0-0-x3-x2-x1-x0 
  
  writeByteCommand(RMW);            //start Read-modify-Write
  for(int i=0; i<2; i++){
    Wire.requestFrom(addr, 2);       //request 2 bytes from slave device
    while(Wire.available()){         //slave may send less than requested
      dat = Wire.read();             //receive a byte as character
    }
  }
  //Serial.println(dat);             // print the data
  //dat = (dat & (0xfe<<(y%8)));
  dat &= ~(1<<(y%8));
  writeByteDat(dat);                //row=bit0--bit7
  writeByteCommand(END);            //end Read-modify-Write 
}

/******************************************
 * clear screen, all pixel off.
 * screen size: 128*64 dot
*******************************************/
void Lcd_st7567s::clear(bool invcolor){
  for(int x=0; x<8; x++){
    writeByteCommand(0xb0 + x);   //y, page address y=1-0-1-1-y3-y2-y1-y0, 1-page with 8-rows
    
    /*******automatically increased by one******/
    writeByteCommand(0x10);       //x, column address x=0-0-0-0-1-x7-x6-x5-x4
    writeByteCommand(0x00);       //x, column address x=0-0-0-0-0-x3-x2-x1-x0
    
    for(int i=0; i<128; i++){
      if (invcolor) {
        writeByteDat(0xff);         //row=bit0--bit7
      }
      else {
        writeByteDat(0x00);         //row=bit0--bit7
      }
    }  
  }
}
///////////////////reserve///////////////////
void Lcd_st7567s::fontSize(int num){
  
}

/******************************************
 * Character display position. x=0-7, y=0-17
*******************************************/
void Lcd_st7567s::cursor(int x, int y){
  if(x>17){x=17;}
  if(y>7){x=7;}
  cursorInit[0]=y;
  cursorInit[1]=x;
}

/******************************************
 * display picture.
*******************************************/
void Lcd_st7567s::displayPicture(const unsigned char picture[], int widthInPixels){
  for(int x=0; x<9; x++){
    writeByteCommand(0xb0 + x);   //y, page address y=1-0-1-1-y3-y2-y1-y0, 1-page with 8-rows
    
    /*******automatically increased by one******/
    writeByteCommand(0x10);       //x, column address x=0-0-0-0-1-x7-x6-x5-x4
    writeByteCommand(0x00);       //x, column address x=0-0-0-0-0-x3-x2-x1-x0

    for(int i=0; i<widthInPixels; i++){
      writeByteDat(pgm_read_word_near(picture+i+x*widthInPixels)); 
      }  
  }
}

/******************************************
 * Writes the data from the font.c file to RAM.
*******************************************/
void Lcd_st7567s::writeFont(int num){
  for(int i=0; i<7; i++){
    //reference: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
    writeByteDat(pgm_read_word_near(font_7x8[num]+i));   
    //Serial.println(pgm_read_word_near(font_7x8[num]+i),HEX); 
    }
}

/******************************************
 * display font.
*******************************************/
void Lcd_st7567s::display(char *str){
  int len = 0;
  len = strlen(str);
  
  writeByteCommand(0xb0 + cursorInit[0]);           //y, page address y=1-0-1-1-y3-y2-y1-y0, 1-page with 8-rows
  /*******automatically increased by one******/
  writeByteCommand(0x10 + cursorInit[1]*7/16);      //x, column address x=0-0-0-0-1-x7-x6-x5-x4
  writeByteCommand(0x00 + cursorInit[1]*7%16);      //x, column address x=0-0-0-0-0-x3-x2-x1-x0

  for(int num=0; num<len; num++){ 
    switch(str[num]){
      case '0': writeFont(0); break;
      case '1': writeFont(1); break;
      case '2': writeFont(2); break;
      case '3': writeFont(3); break;
      case '4': writeFont(4); break;
      case '5': writeFont(5); break;
      case '6': writeFont(6); break;
      case '7': writeFont(7); break;
      case '8': writeFont(8); break;
      case '9': writeFont(9); break;
      case 'a': writeFont(10); break;
      case 'b': writeFont(11); break;
      case 'c': writeFont(12); break;
      case 'd': writeFont(13); break;
      case 'e': writeFont(14); break;
      case 'f': writeFont(15); break;
      case 'g': writeFont(16); break;
      case 'h': writeFont(17); break;
      case 'i': writeFont(18); break;
      case 'j': writeFont(19); break;
      case 'k': writeFont(20); break;
      case 'l': writeFont(21); break;
      case 'm': writeFont(22); break;
      case 'n': writeFont(23); break;
      case 'o': writeFont(24); break;
      case 'p': writeFont(25); break;
      case 'q': writeFont(26); break;
      case 'r': writeFont(27); break;
      case 's': writeFont(28); break;
      case 't': writeFont(29); break;
      case 'u': writeFont(30); break;
      case 'v': writeFont(31); break;
      case 'w': writeFont(32); break;
      case 'x': writeFont(33); break;
      case 'y': writeFont(34); break;
      case 'z': writeFont(35); break;
      case 'A': writeFont(36); break;
      case 'B': writeFont(37); break;
      case 'C': writeFont(38); break;
      case 'D': writeFont(39); break;
      case 'E': writeFont(40); break;
      case 'F': writeFont(41); break;
      case 'G': writeFont(42); break;
      case 'H': writeFont(43); break;
      case 'I': writeFont(44); break;
      case 'J': writeFont(45); break;
      case 'K': writeFont(46); break;
      case 'L': writeFont(47); break;
      case 'M': writeFont(48); break;
      case 'N': writeFont(49); break;
      case 'O': writeFont(50); break;
      case 'P': writeFont(51); break;
      case 'Q': writeFont(52); break;
      case 'R': writeFont(53); break;
      case 'S': writeFont(54); break;
      case 'T': writeFont(55); break;
      case 'U': writeFont(56); break;
      case 'V': writeFont(57); break;
      case 'W': writeFont(58); break;
      case 'X': writeFont(59); break;
      case 'Y': writeFont(60); break;
      case 'Z': writeFont(61); break;
      case '!': writeFont(62); break;
      case '"': writeFont(63); break;
      case '#': writeFont(64); break;
      case '$': writeFont(65); break;
      case '%': writeFont(66); break;
      case '&': writeFont(67); break;
      case '\'': writeFont(68); break;
      case '(': writeFont(69); break;
      case ')': writeFont(70); break;
      case '*': writeFont(71); break;
      case '+': writeFont(72); break;
      case ',': writeFont(73); break;
      case '-': writeFont(74); break;
      case '/': writeFont(75); break;
      case ':': writeFont(76); break;
      case ';': writeFont(77); break;
      case '<': writeFont(78); break;
      case '=': writeFont(79); break;
      case '>': writeFont(80); break;
      case '?': writeFont(81); break;
      case '@': writeFont(82); break;
      case '{': writeFont(83); break;
      case '|': writeFont(84); break;
      case '}': writeFont(85); break;
      case '~': writeFont(86); break;
      case ' ': writeFont(87); break;
      case '.': writeFont(88); break;
      case '^': writeFont(89); break;
      case '_': writeFont(90); break;
      case '`': writeFont(91); break;
      case '[': writeFont(92); break;
      case '\\': writeFont(93); break;
      case ']': writeFont(94); break;
      default: break;
    }  
  }
}

void Lcd_st7567s::drawLine(int x1, int y1, int x2, int y2, bool invcolor) {

  int tmp;
  int x,y;
  int dx, dy;
  int err;
  int ystep;

  int swapxy = 0;

  if ( x1 > x2 ) dx = x1-x2; else dx = x2-x1;
  if ( y1 > y2 ) dy = y1-y2; else dy = y2-y1;

  if ( dy > dx ) 
  {
    swapxy = 1;
    tmp = dx; dx =dy; dy = tmp;
    tmp = x1; x1 =y1; y1 = tmp;
    tmp = x2; x2 =y2; y2 = tmp;
  }
  if ( x1 > x2 ) 
  {
    tmp = x1; x1 =x2; x2 = tmp;
    tmp = y1; y1 =y2; y2 = tmp;
  }
  err = dx >> 1;
  if ( y2 > y1 ) ystep = 1; else ystep = -1;
  y = y1;

  for( x = x1; x <= x2; x++ )
  {
    if ( swapxy == 0 )
      if (invcolor) {
        clearPixel(x, y);
      }
      else {
        displayPixel(x, y);
      }
    else 
      if (invcolor) {
        clearPixel(y, x);
      }
      else {
        displayPixel(y, x); 
      }
    err -= dy;
    if ( err < 0 ) 
    {
      y += ystep;
      err += dx;
    }
  }  
}
/*==============================================*/
/* Circle */
void Lcd_st7567s::drawCircleSection(int x, int y, int x0, int y0, int option, bool invcolor, bool solid)
{
    /* upper right */
    if ( option & DRAW_UPPER_RIGHT )
    {
      if (solid) {
        drawLine(x0 + x, y0 - y, x0, y0 - y, invcolor);
        drawLine(x0 + y, y0 - x, x0, y0 - x, invcolor);
      }
      else {
        if (invcolor) {
          clearPixel(x0 + x, y0 - y);
          clearPixel(x0 + y, y0 - x);        
        }
        else {
          displayPixel(x0 + x, y0 - y);
          displayPixel(x0 + y, y0 - x);
        }        
      }
    }
    
    /* upper left */
    if ( option & DRAW_UPPER_LEFT )
    {
      if (solid) {
        drawLine(x0 - x, y0 - y, x0, y0 - y, invcolor);
        drawLine(x0 - y, y0 - x, x0, y0 - x, invcolor);
      }
      else {
        if (invcolor) {
          clearPixel(x0 - x, y0 - y);
          clearPixel(x0 - y, y0 - x);
        }
        else {
          displayPixel(x0 - x, y0 - y);
          displayPixel(x0 - y, y0 - x);
        }
      }
    }
    
    /* lower right */
    if ( option & DRAW_LOWER_RIGHT )
    {
      if (solid) {
        drawLine(x0 + x, y0 + y, x0, y0 + y, invcolor);
        drawLine(x0 + y, y0 + x, x0, y0 + x, invcolor);
      }
      else {
        if (invcolor) {
          clearPixel(x0 + x, y0 + y);
          clearPixel(x0 + y, y0 + x);
        }
        else {
          displayPixel(x0 + x, y0 + y);
          displayPixel(x0 + y, y0 + x);
        }
      }
    }
    
    /* lower left */
    if ( option & DRAW_LOWER_LEFT )
    {
      if (solid) {
        drawLine(x0 - x, y0 + y, x0, y0 + y, invcolor);
        drawLine(x0 - y, y0 + x, x0, y0 + x, invcolor);
      }
      else {
        if (invcolor) {
          clearPixel(x0 - x, y0 + y);
          clearPixel(x0 - y, y0 + x);
        }
        else {
          displayPixel(x0 - x, y0 + y);
          displayPixel(x0 - y, y0 + x);
        }
      }
    }
}

void Lcd_st7567s::drawCircle(int x0, int y0, int rad, int option, bool invcolor, bool solid)
{
    int f;
    int ddF_x;
    int ddF_y;
    int x;
    int y;

    f = 1;
    f -= rad;
    ddF_x = 1;
    ddF_y = 0;
    ddF_y -= rad;
    ddF_y *= 2;
    x = 0;
    y = rad;

    drawCircleSection(x, y, x0, y0, option, invcolor, solid);
    
    while ( x < y )
    {
      if (f >= 0) 
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;

      drawCircleSection(x, y, x0, y0, option, invcolor, solid);    
    }
}
/*==============================================*/
