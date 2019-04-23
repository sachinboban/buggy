#include "drive.h"
#include "receiver.h"
#include "Arduino.h"

#define TURN_GEAR (GEAR_1)

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
  int gear;

  gear = GEAR_0;
  dir = DRIVE_FWD;

  receiver_read(&dir, &gear);

  if ((DRIVE_LEFT == dir)
      || (DRIVE_RIGHT == dir)) {
    gear = TURN_GEAR;
  }

  if (GEAR_0 == gear)
    drive_stop();
  else
    drive_move(dir, gear);
}
