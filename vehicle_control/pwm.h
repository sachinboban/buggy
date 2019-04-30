#ifndef PWM_H
#define PWM_H

#include "Arduino.h"

/*
 * @brief Initialize PWM
 */
void pwm_init();

/*
 * @brief Write the value of the PWM PIN
 *
 * @note The given pin must already be configured
 *       as GPIO_PIN_DIR_OUTPUT before calling
 *       this API.
 * @note Only GPIO_PIN_5 and GPIO_PIN_6 can
 *       configured this way.
 *
 * @pin       PWM pin (GPIO_PIN_xx)
 * @val       Value of the PWM pin (0-255)
 */
void pwm_write(uint8_t pin, uint8_t val);

#endif /* PWM_H */
