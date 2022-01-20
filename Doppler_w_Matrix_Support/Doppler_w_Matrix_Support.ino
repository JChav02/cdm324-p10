#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial14.h"

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
#define pin 5

int kphConst = 44;
String strVal;
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD(){
  dmd.scanDisplayBySPI();
}

void dmd_txt(String txt){
  dmd.clearScreen(true);
  char newString[10];
  int stringLength = txt.length();
  txt.toCharArray(newString, stringLength+1);
  dmd.drawString(0, 5, newString, stringLength, GRAPHICS_NORMAL);
}

void setup(){
  Timer1.initialize(500);
  Timer1.attachInterrupt(ScanDMD);

  dmd.clearScreen(true);
  dmd.selectFont(Arial_14);
  Serial.begin(115200);

  pinMode(pin, INPUT);
}

void loop(){
  noInterrupts();
  unsigned long int pulse = 0;
  pulse = pulseIn(pin, HIGH);
  interrupts();

  unsigned int frequency = 1000000 / pulse;
  unsigned int spd = frequency / kphConst;

  strVal = String(spd);
  strVal = strVal + " kph";

  dmd_txt(strVal);

  delay(500);
}
