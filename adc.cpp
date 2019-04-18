#include "adc.h"
#include "reg_ops.h"

void adc_enable()
{
  /* Enable the ADC */
  REGISTER_BIT_SET(ADC_REG_CSRA, ADC_ENABLE, ADC_ENABLE_BIT);
}

void adc_disable()
{
  /* Disable the ADC */
  REGISTER_BIT_CLR(ADC_REG_CSRA, ADC_ENABLE_BIT);
}

/*
 * @brief Set the ADC reference voltage
 *
 * Internal helper function to set the ADC reference volatage.
 *
 * @mode  Shall be one of the ADC_REF_VOLTAGE_xxx macros
 */
static void adc_set_ref_voltage(uint8_t mode)
{
  uint8_t val;
  
  val = REGISTER_GET(ADC_REG_MUX);
  val |= (mode << 6);
  REGISTER_SET(ADC_REG_MUX, val);
}

/*
 * @brief Set the pinmux
 *
 * Internal helper function to set the ADC pinmux
 *
 * @pin   Shall be one of the ADC_PIN_x macros macros
 */
static void adc_set_pinmux(uint8_t pin)
{
  uint8_t val;

  val = REGISTER_GET(ADC_REG_MUX);
  val &= ~(0xF);
  val |= (pin - ADC_PIN_0);
  REGISTER_SET(ADC_REG_MUX, val);
}

int adc_read(uint8_t pin)
{
  int retval = 0;

  /* Set the ADC reference voltate */
  adc_set_ref_voltage(ADC_REF_VOLTAGE_DEF);

  /* Set pin mux */
  adc_set_pinmux(pin);
  
  /* Start conversion */
  REGISTER_BIT_SET(ADC_REG_CSRA, ADC_START_CONV, ADC_START_CONV_BIT);

  /* Wait for the conversion to complete */
  while(1 == (REGISTER_GET(ADC_REG_CSRA) >> ADC_START_CONV_BIT) & 0x1);

  /* Read the low and high registers */
  retval = REGISTER_GET(ADC_REG_LOW);
  retval |= (REGISTER_GET(ADC_REG_HIGH) << 8);

  return retval;
}
