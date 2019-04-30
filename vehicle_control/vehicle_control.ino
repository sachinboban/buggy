#include "drive.h"
#include "receiver.h"
#include "distance.h"
#include "Arduino.h"

#define SAFE_DIST (20)

void setup()
{
  int i;
  /* Set the serial port baud rate */
  Serial.begin(9600);

  /* Enable receiver */
  receiver_init();

  /* Enable UV sensor */
  distance_init();

  /* Enable drive system */
  drive_init();
}

void loop()
{
  uint8_t dir;
  int gear;
  int dist_cm;
  uint8_t sub_dir;

  gear = GEAR_0;
  dir = DRIVE_FWD;

  dist_cm = get_distance_cm();

  receiver_read(&dir, &gear);

  sub_dir = 0;

  if ((DRIVE_LEFT == dir)
      || (DRIVE_RIGHT == dir)) {
    /*
     * Get the sub-direction and sub-direction speed.
     */
    sub_dir = (gear >> 1);
    gear = (gear & 1);

    if ((DRIVE_FWD == dir) && (GEAR_0 == gear)) {
      drive_stop();
    } else if ((DRIVE_FWD == dir) && (SAFE_DIST >=  dist_cm)){
      drive_stop();
    } else {
      drive_move(dir, gear, sub_dir);
    }
  }
}
