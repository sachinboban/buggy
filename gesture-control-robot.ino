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

  /* Enable motors */
  motor_init();
}

void test_adc()
{
  analogRead(ADC_PIN_0);
  Serial.print("\nx = ");
  Serial.print(adc_read(ADC_PIN_0));
  Serial.print("\nAnax = ");
  Serial.print(analogRead(ADC_PIN_0));
}

void test_motor()
{
  motor_stop_all();
  motor_configure(MTR_SET_L, MTR_SET_ROT_CLK, 200);
  motor_configure(MTR_SET_R, MTR_SET_ROT_CLK, 200);
  motor_rotate(MTR_SET_L);
  motor_rotate(MTR_SET_R);
  delay(3000);
  motor_stop_all();
  motor_configure(MTR_SET_L, MTR_SET_ROT_ACLK, 100);
  motor_configure(MTR_SET_R, MTR_SET_ROT_CLK, 100);
  motor_rotate(MTR_SET_L);
  motor_rotate(MTR_SET_R);
  delay(500);
  motor_configure(MTR_SET_L, MTR_SET_ROT_CLK, 200);
  motor_configure(MTR_SET_R, MTR_SET_ROT_CLK, 200);
  motor_rotate(MTR_SET_L);
  motor_rotate(MTR_SET_R);
  delay(3000);
  motor_stop_all();
  motor_configure(MTR_SET_L, MTR_SET_ROT_CLK, 100);
  motor_configure(MTR_SET_R, MTR_SET_ROT_ACLK, 100);
  motor_rotate(MTR_SET_L);
  motor_rotate(MTR_SET_R);
  delay(500);
}

void loop()
{
  //test_adc();
  test_motor();
  delay(1000);
}
