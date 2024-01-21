#ifdef ARDUINO_ARCH_AVR
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

// 'smile', 64x64px
const unsigned char smile [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
	0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x81, 
	0xc1, 0xe0, 0xf0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xc1, 
	0x81, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x03, 0x01, 0x00, 0xe0, 0xf0, 0xfc, 0xfe, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x03, 0x03, 0x03, 0x03, 0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x03, 0x03, 0x03, 0x03, 0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0xfc, 0xf0, 0xe0, 0x00, 0x01, 0x03, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x03, 
	0x03, 0x07, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x03, 
	0x03, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0xc0, 0x80, 0x00, 0x07, 0x0f, 0x3f, 0x7f, 0xff, 0xff, 
	0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x81, 0x83, 0x07, 0x0f, 0x0f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 
	0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x07, 0x83, 0x81, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 
	0xff, 0xff, 0x7f, 0x3f, 0x0f, 0x07, 0x00, 0x80, 0xc0, 0xf0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x81, 
	0x83, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7e, 0x7e, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 
	0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0x7e, 0x7e, 0x7f, 0x3f, 0x3f, 0x3f, 0x1f, 0x0f, 0x0f, 0x07, 0x83, 
	0x81, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
	0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};