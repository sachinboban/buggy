#include "pwm.h"
#include "gpio.h"
#include "reg_ops.h"

#define PWM_REG_TCCR_0_A  (0x44)
#define PWM_REG_TCCR_0_B  (0x45)
#define PWM_REG_OCR_0_A   (0x47)
#define PWM_REG_OCR_0_B   (0x48)

void pwm_init()
{
  
  REGISTER_BIT_SET(PWM_REG_TCCR_0_A, 1, 0);
  REGISTER_BIT_SET(PWM_REG_TCCR_0_A, 1, 1);
  REGISTER_BIT_CLR(PWM_REG_TCCR_0_A, 4);
  REGISTER_BIT_CLR(PWM_REG_TCCR_0_A, 5);
  REGISTER_BIT_CLR(PWM_REG_TCCR_0_A, 6);
  REGISTER_BIT_CLR(PWM_REG_TCCR_0_A, 7);

  REGISTER_BIT_SET(PWM_REG_TCCR_0_B, 1, 0);
  REGISTER_BIT_SET(PWM_REG_TCCR_0_B, 1, 1);
  REGISTER_BIT_CLR(PWM_REG_TCCR_0_B, 2);
  REGISTER_BIT_SET(PWM_REG_TCCR_0_B, 1, 3);
}

void pwm_write(uint8_t pin, uint8_t val)
{
  if (0 == val) {
    gpio_write(pin, GPIO_LOW);
} else if (255 == val) {
    gpio_write(pin, GPIO_HIGH);
  } else {
    switch(pin)
    {
      case GPIO_PIN_5:
        REGISTER_SET(PWM_REG_OCR_0_B, val);
        break;

      case GPIO_PIN_6:
        REGISTER_SET(PWM_REG_OCR_0_A, val);
        break;

      default:
        break;
    }
  }
}
