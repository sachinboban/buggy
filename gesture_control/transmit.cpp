#include "transmit.h"
#include "Arduino.h"

#define SPD_MIN (0)
#define SPD_MAX (1023)

void transmit_init()
{
  /* Initialize the required pins */
}

void transmit(uint8_t dir, int spd)
{
  int mapped_spd;
  int en0_val, en1_val, en2_val, en3_val;

   mapped_speed = map(spd, SPD_MIN, SPD_MAX, 0, 3);

  en0_val = LOW;
  en1_val = LOW;
  en2_val = LOW;
  en3_val = LOW;
  if (TRANS_DIR_FWD == dir) {
    en0_val = LOW;
    en1_val = LOW;
  } else if(TRANS_DIR_BKWD == dir) {
    en0_val = HIGH;
    en1_val = LOW;
  } else if(TRANS_DIR_LEFT == dir) {
    en0_val = LOW;
    en1_val = HIGH;
  } else if(TRANS_DIR_RIGHT == dir) {
    en0_val = HIGH;
    en1_val = HIGH;
  }

  if (0 == mapped_spd) {
    en2_val = LOW;
    en3_val = LOW;
  } else if(1 == dir) {
    en2_val = HIGH;
    en3_val = LOW;
  } else if(2 == dir) {
    en2_val = LOW;
    en3_val = HIGH;
  } else if(3 == dir) {
    en2_val = HIGH;
    en3_val = HIGH;
  }

  /*
   * TODO: Write the pins */
   */
}
