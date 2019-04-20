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
  motor_init(MTR_ID_L1);
  motor_init(MTR_ID_R1);
  motor_init(MTR_ID_L2);
  motor_init(MTR_ID_R2);
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
  /* Forward */
  motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, 255);
  motor_configure(MTR_ID_R1, MTR_ROT_DIR_CLK, 255);
  motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, 255);
  motor_configure(MTR_ID_R2, MTR_ROT_DIR_CLK, 255);
  motor_rotate(MTR_ID_L1);
  motor_rotate(MTR_ID_R1);
  motor_rotate(MTR_ID_L2);
  motor_rotate(MTR_ID_R2);
//
//  /* stop all */
//  motor_stop(MTR_ID_L1);
//  motor_stop(MTR_ID_R1);
//  motor_stop(MTR_ID_L2);
//  motor_stop(MTR_ID_R2);
//  delay(500);
//
//  /* turn left */
//  motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, 0);
//  motor_configure(MTR_ID_R1, MTR_ROT_DIR_CLK, 100);
//  motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, 0);
//  motor_configure(MTR_ID_R2, MTR_ROT_DIR_CLK, 100);
//  motor_rotate(MTR_ID_L1);
//  motor_rotate(MTR_ID_L2);
//  motor_rotate(MTR_ID_R1);
//  motor_rotate(MTR_ID_R2);
//  delay(500);
//
//  /* stop all */
//  motor_stop(MTR_ID_L1);
//  motor_stop(MTR_ID_R1);
//  motor_stop(MTR_ID_L2);
//  motor_stop(MTR_ID_R2);
//  delay(500);
//  
//  /* Forward */
//  motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, 200);
//  motor_configure(MTR_ID_R1, MTR_ROT_DIR_CLK, 200);
//  motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, 200);
//  motor_configure(MTR_ID_R2, MTR_ROT_DIR_CLK, 200);
//  motor_rotate(MTR_ID_L1);
//  motor_rotate(MTR_ID_R1);
//  motor_rotate(MTR_ID_L2);
//  motor_rotate(MTR_ID_R2);
//  delay(3000);
//
//  /* stop all */
//  motor_stop(MTR_ID_L1);
//  motor_stop(MTR_ID_R1);
//  motor_stop(MTR_ID_L2);
//  motor_stop(MTR_ID_R2);
//  delay(500);
//
//  /* turn right */
//  motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, 100);
//  motor_configure(MTR_ID_R1, MTR_ROT_DIR_ACLK, 0);
//  motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, 100);
//  motor_configure(MTR_ID_R2, MTR_ROT_DIR_ACLK, 0);
//  motor_rotate(MTR_ID_R1);
//  motor_rotate(MTR_ID_R2);
//  motor_rotate(MTR_ID_L1);
//  motor_rotate(MTR_ID_L2);
//  delay(500);
//
//  /* stop all */
//  motor_stop(MTR_ID_L1);
//  motor_stop(MTR_ID_R1);
//  motor_stop(MTR_ID_L2);
//  motor_stop(MTR_ID_R2);
//  delay(500);
}

void loop()
{
  //test_adc();
  test_motor();
}
