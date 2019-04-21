#ifndef ADC_H
#define ADC_H

#include "Arduino.h"

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
