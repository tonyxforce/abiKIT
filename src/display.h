#include <Wire.h>
#include <U8g2lib.h>

extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

extern bool displaySetup();
extern bool displayLoop();

void nextLine();
void printText(double text);
void printText(String text);