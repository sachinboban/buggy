#include "drive.h"
#include "receiver.h"
#include "distance.h"
#include "Arduino.h"

#define TURN_GEAR (GEAR_1)
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

  gear = GEAR_0;
  dir = DRIVE_FWD;

  dist_cm = get_distance_cm();

  receiver_read(&dir, &gear);

  if ((DRIVE_LEFT == dir)
      || (DRIVE_RIGHT == dir)) {
    gear = TURN_GEAR;
  }

  if (GEAR_0 == gear) {
    drive_stop();
  } else if ((DRIVE_FWD == dir)
            && (SAFE_DIST >=  dist_cm)){
    drive_stop();
  } else {
    drive_move(dir, gear);
  }
}
