#include "adc.h"

void adc_enable()
{
	/* Enable the ADC */
	ADCSRA |= (ADC_ENABLE << ADC_ENABLE_BIT_SHIFT);
}

void adc_disable()
{
	/* Enable the ADC */
	ADCSRA &= ~(ADC_ENABLE << ADC_ENABLE_BIT_SHIFT);
}

int adc_read(uint8_t pin)
{
  int retval = 0;
  uint8_t val;
  
  /* Enable the ADC */
  ADCSRA |= (1 << 7);
  
  /* Set the Analog Reference value */
  ADMUX |= (ADC_REF_VOLTAGE_DEF << 6);

  /* Set pin mux */
  val = ADMUX;
  val &= ~(0xF);
  val |= (pin - ADC_PIN_0);
  ADMUX = val;
 
  
  /* Start conversion */
  ADCSRA |= (1 << 6);

  /* Wait for the conversion to complete */
  while(1 == (ADCSRA >> 6) & 0x1);

  /* Read the low and high registers */
  retval = ADCL;
  retval |= (ADCH << 8);

  return retval;
}
