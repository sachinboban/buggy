#include "adc.h"
#include "transmit.h"
#include "Arduino.h"

#define X_REF (505)
#define Y_REF (509)

#define SPD_MIN (0)
#define SPD_MAX (75)

#define MOVE_MIN  (25)

void setup()
{
  Serial.begin(9600);
  /* Enable ADC */
  adc_enable();

  /* Enable the transmition block */
  transmit_init();
}

/*
 * Set the speed bits according to
 * y deviation for left/right movement
 */
int get_speed_bits(int y_dev)
{
  int spd;

  if (abs(y_dev) < MOVE_MIN) {
    spd = 0;
  } else {
    if (y_dev > 0)
      spd = 1;
    else
      spd = 3;
  }

  return spd;
}

void loop()
{
  int adc_x, x_dev;
  int adc_y, y_dev;
  uint8_t dir;
  uint8_t spd;

  adc_x = adc_read(ADC_PIN_0);
  adc_y = adc_read(ADC_PIN_1);

  /* Calculate devition from reference */
  x_dev = adc_x - X_REF;
  y_dev = adc_y - Y_REF;

  dir = TRANS_DIR_FWD;
  spd = 0;

  if (abs(x_dev) > MOVE_MIN) {
    if (x_dev > 0) {
       dir = TRANS_DIR_RIGHT;
    } else {
      dir = TRANS_DIR_RIGHT;
    }

    if (abs(y_dev) > MOVE_MIN) {
      spd = get_speed_bits(y_dev);
    } else {
      spd = 0;
    }
  } else {
    if (abs(y_dev) > MOVE_MIN) {
      if (y_dev > 0) {
        dir = TRANS_DIR_FWD;
        spd = abs(y_dev);
      } else {
        dir = TRANS_DIR_BKWD;
        spd = abs(y_dev);
      }
    } else {
      dir = TRANS_DIR_FWD;
      spd = 0;
    }
  }

  if ((abs(x_dev) > MOVE_MIN)
      || (abs(y_dev) > MOVE_MIN)) {
      if ((x_dev > 0) && (abs(x_dev) > MOVE_MIN)) {
        dir = TRANS_DIR_RIGHT;
        spd = get_speed_bits(y_dev);
      } else if ((x_dev < 0) && (abs(x_dev) > MOVE_MIN)){
        dir = TRANS_DIR_LEFT;
        spd = get_speed_bits(y_dev);
      } else if ((y_dev > 0) && (abs(y_dev) > MOVE_MIN)) {
        dir = TRANS_DIR_FWD;
        spd = map(abs(y_dev), SPD_MIN, SPD_MAX, 0, 3);
      } else if ((y_dev < 0) && (abs(y_dev) > MOVE_MIN)) {
        dir = TRANS_DIR_BKWD;
        spd = map(abs(y_dev), SPD_MIN, SPD_MAX, 0, 3);
      } else {
        dir = TRANS_DIR_FWD;
        spd = 0;
      }

  } else {
    dir = TRANS_DIR_FWD;
    spd = 0;
  }

  transmit(dir, spd);
}
