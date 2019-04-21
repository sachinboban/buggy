#include "adc.h"
#include "Arduino.h"

#define X_REF (400)
#define Y_REF (400)

#define MOVE_MIN  (50)

void setup
{
  /* Enable ADC */
  adc_enable();
  analogRead(ADC_PIN_0);

  /* Enable the transmition block */
  transmit_init();
}

void loop()
{
  int adc_x, x_dev;
  int adc_y, y_dev;
  int adc_z, z_dev;
  uint8_t dir;

  adc_x = adc_read(ADC_PIN_0);
  adc_y = adc_read(ADC_PIN_1);
  adc_z = adc_read(ADC_PIN_2);

  /* Calculate devition from reference */
  x_dev = adc_x - X_REF;
  y_dev = adc_y - Y_REF;

  if ((abs(x_dev) > MOVE_MIN)
      || (abs(y_dev) > MOVE_MIN)) {
    if (abs(x_dev) > abs(y_dev)) {
      /* Move left/right */
      if (x_dev > 0) {
        transmit(MOVE_RIGHT, abs(x_dev));
      } else {
        transmit(MOVE_LEFT, abs(x_dev));
      }
    } else {
      /* Move fwd/bkwd */
      if (y_dev > 0) {
        transmit(MOVE_FWD, abs(y_dev));
      } else {
        transmit(MOVE_BKWD, abs(y_dev));
      }
    }
  } else {
    transmit(MOVE_FWD, 0);
  }
}
