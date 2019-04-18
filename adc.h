#ifndef ADC_H
#define ADC_H

#include "Arduino.h"

/*
 * ADC Registers
 */
#define ADC_REG_LOW		(0x78)	/* ADC Low Data Register */
#define ADC_REG_HIGH	(0x79)	/* ADC High Data Register */
#define ADC_REG_CSRA	(0x7A)	/* ADC Control and Status Register A */
#define ADC_REG_CSRB	(0x7B)	/* ADC Control and Status Register B */
#define ADC_REG_MUX		(0x7C)	/* ADC Multiplexer Selection Register */

/*
 * ADC Multiplexer Selection Register
 */
 
/* Volage Reference Selection */
#define ADC_REF_VOLTAGE_AREF		(0x0)	/* AREF pin (external) */
#define ADC_REF_VOLTAGE_DEF			(0x1)	/* Default ref voltage (5V) */
#define ADC_REF_VOLTAGE_RESVD		(0x2)	/* Reserved */
#define ADC_REF_VOLTAGE_INT			(0x3)	/* Internal ref voltage (1.1V) */

/* Voltage Reference Selection bitshift */
#define ADC_REF_VOLTAGE_BIT_SHIFT	(0x6)

/*
 * ADC Control and Status Register A
 */
#define ADC_ENABLE				(0x1)	/* Enable ADC */
#define ADC_ENABLE_BIT_SHIFT	(0x7)	/* ADC Enable bit shift */

#define ADC_START_CONV				(0x1)	/* Start ADC conversion */
#define ADC_START_CONV_BIT_SHIFT	(0x6)	/* Start ADC conversion bit shift */

/*
 * Analog Pins
 */
#define ADC_PIN_0	(14)	/* Analog Pin 0 */
#define ADC_PIN_1	(15)	/* Analog Pin 1 */
#define ADC_PIN_2	(16)	/* Analog Pin 2 */

/*
 * @brief Enable ADC block
 */
void adc_enable();

/*
 * @brief Read analog value
 *
 * Get the value of the analog signal at the given analog pin. This function
 * polls on the CSRA register determine whether the conversion is complete or
 * not. The value of @pin shall be one of the ADC_PIN_x macros.
 */
int adc_read(uint8_t pin);

/*
 * @brief Disale ADC block
 */
void adc_disable();

#endif	/* ADC_H */
