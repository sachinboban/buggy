#include "adc.h"
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

void loop()
{
  test_adc();
  delay(1000);
}
