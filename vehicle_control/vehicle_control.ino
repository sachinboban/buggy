#include "drive.h"
#include "receiver.h"
#include "Arduino.h"

void setup()
{
  int i;
  /* Set the serial port baud rate */
  Serial.begin(9600);

  DDRC &= ~((1 << 2) | (1 << 1) | (1 << 0));

  /* Enable drive system */
  drive_init();

  /* Enable receiver */
  receiver_init();
}

void loop()
{
  uint8_t dir;
  int spd;

  spd = 0;
  dir = DRIVE_FWD;

  receiver_read(&dir, &spd);
  if (0 == spd)
    drive_stop();
  else
    drive_move(dir, spd);
}
