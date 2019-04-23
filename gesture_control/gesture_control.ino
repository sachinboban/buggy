#include "adc.h"
#include "transmit.h"
#include "Arduino.h"

#define X_REF (505)
#define Y_REF (509)

#define MOVE_MIN  (50)

void setup()
{
  Serial.begin(9600);
  /* Enable ADC */
  adc_enable();

  /* Enable the transmition block */
  transmit_init();
}

void loop()
{
  int adc_x, x_dev;
  int adc_y, y_dev;

  adc_x = adc_read(ADC_PIN_0);
  adc_y = adc_read(ADC_PIN_1);

  /* Calculate devition from reference */
  x_dev = adc_x - X_REF;
  y_dev = adc_y - Y_REF;

  if ((abs(x_dev) > MOVE_MIN)
      || (abs(y_dev) > MOVE_MIN)) {
    if (abs(x_dev) > abs(y_dev)) {
      /* Move left/right */
      if (x_dev > 0) {
        transmit(TRANS_DIR_RIGHT, abs(x_dev));
      } else {
        transmit(TRANS_DIR_LEFT, abs(x_dev));
      }
    } else {
      /* Move fwd/bkwd */
      if (y_dev > 0) {
        transmit(TRANS_DIR_FWD, abs(y_dev));
      } else {
        transmit(TRANS_DIR_BKWD, abs(y_dev));
      }
    }
  } else {
    transmit(TRANS_DIR_FWD, 0);
  }
}
