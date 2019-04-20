#include "adc.h"
#include "motor.h"
#include "Arduino.h"

void setup()
{
  /* Set the serial port baud rate */
  Serial.begin(9600);

  DDRC &= ~((1 << 2) | (1 << 1) | (1 << 0));

  /* Enable ADC */
  adc_enable();
  analogRead(ADC_PIN_0);

  /* Enable motors */
  motor_init(MTR_ID_L1);
  motor_init(MTR_ID_R1);
  motor_init(MTR_ID_L2);
  motor_init(MTR_ID_R2);
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
