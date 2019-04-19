#include "adc.h"
#include "move.h"
#include "Arduino.h"

void setup()
{
  DDRC &= ~((1 << 2) | (1 << 1) | (1 << 0));

  /* Enable ADC */
  adc_enable();

  /* Set the serial port baud rate */
  Serial.begin(9600);
}

void test_adc()
{
  analogRead(ADC_PIN_0);
  Serial.print("\nx = ");
  Serial.print(adc_read(ADC_PIN_0));
  Serial.print("\nAnax = ");
  Serial.print(analogRead(ADC_PIN_0));
}

void test_move()
{
  move_stop();
  delay(1);
  move_forward();
  delay(2);
  move_stop();
  move_right();
  delay(1);
  move_stop();
  move_left();
  delay(1);
  move_forward();
  delay(2);
  move_stop();
  move_backward();
  delay(2);
  move_stop();
}

void loop()
{
  //test_adc();
  test_move();
  delay(1000);
}
