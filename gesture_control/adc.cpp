#include "adc.h"
#include "gpio.h"
#include "reg_ops.h"

/*
 * ADC Registers
 */
#define ADC_REG_LOW   (0x78)  /* ADC Low Data Register */
#define ADC_REG_HIGH  (0x79)  /* ADC High Data Register */
#define ADC_REG_CSRA  (0x7A)  /* ADC Control and Status Register A */
#define ADC_REG_CSRB  (0x7B)  /* ADC Control and Status Register B */
#define ADC_REG_MUX   (0x7C)  /* ADC Multiplexer Selection Register */

/*
 * ADC Multiplexer Selection Register
 */
 
/* Volage Reference Selection */
#define ADC_REF_VOLTAGE_AREF  (0x0) /* AREF pin (external) */
#define ADC_REF_VOLTAGE_DEF   (0x1) /* Default ref voltage (5V) */
#define ADC_REF_VOLTAGE_RESVD (0x2) /* Reserved */
#define ADC_REF_VOLTAGE_INT   (0x3) /* Internal ref voltage (1.1V) */


#define ADC_REF_VOLTAGE_BIT (0x6) /* Voltage Reference Selection bit */

/*
 * ADC Control and Status Register A
 */
#define ADC_ENABLE      (0x1) /* Enable ADC */
#define ADC_ENABLE_BIT  (0x7) /* ADC Enable bit shift */

#define ADC_START_CONV      (0x1) /* Start ADC conversion */
#define ADC_START_CONV_BIT  (0x6) /* Start ADC conversion bit */

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
 * Internal helper function to set the ADC reference voltage.
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

  REGISTER_BIT_SET(ADC_REG_CSRA, ADC_ENABLE, ADC_ENABLE_BIT);

  /* Set the ADC reference voltate */
  adc_set_ref_voltage(ADC_REF_VOLTAGE_DEF);

  /* Set pin mux */
  adc_set_pinmux(pin);
  
  /* Start conversion */
  REGISTER_BIT_SET(ADC_REG_CSRA, ADC_START_CONV, ADC_START_CONV_BIT);

  /* Wait for the conversion to complete */
  while((REGISTER_GET(ADC_REG_CSRA) & (1 << ADC_START_CONV_BIT)));

  /* Read the low and high registers */
  retval = REGISTER_GET(ADC_REG_LOW);
  retval |= (REGISTER_GET(ADC_REG_HIGH) << 8);

  return retval;
}
