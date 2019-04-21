#include "drive.h"
#include "Arduino.h"

void setup()
{
  int i;
  /* Set the serial port baud rate */
  Serial.begin(9600);

  DDRC &= ~((1 << 2) | (1 << 1) | (1 << 0));

  /* Enable drive system */
  drive_init();
}

void loop()
{
  /*
   * TODO:
   * Read the Decoder pins:
   * (D_1, D_0) conveys the direction of movement
   * (D_3, D_2) conveys the speed for the movement
   */
}
