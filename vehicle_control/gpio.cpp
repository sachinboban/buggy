#include "gpio.h"
#include "reg_ops.h"
#include "Arduino.h"

/* GPIO Registers */
#define GPIO_REG_PIN_B    (0x23)  /* Port B Input register */
#define GPIO_REG_DDR_B    (0x24)  /* Port B Data register */
#define GPIO_REG_PORT_B   (0x25)  /* Port B Data direction register */
#define GPIO_REG_PIN_C    (0x26)  /* Port C Input register */
#define GPIO_REG_DDR_C    (0x27)  /* Port C Data register */
#define GPIO_REG_PORT_C   (0x28)  /* Port C Data direction register */
#define GPIO_REG_PIN_D    (0x29)  /* Port D Input register */
#define GPIO_REG_DDR_D    (0x2A)  /* Port D Data register */
#define GPIO_REG_PORT_D   (0x2B)  /* Port D Data direction register */

void gpio_set_mode(uint8_t pin, uint8_t dir_mode)
{
  uint8_t ddr_addr;
  uint8_t bit_offset;

  if ((GPIO_PIN_A5 < pin)
      || (GPIO_PIN_DIR_OUTPUT < dir_mode)) {
    return;
  }

  if ((GPIO_PIN_0 <= pin)
      && (GPIO_PIN_7 >= pin)) {
    /* Port D */
    ddr_addr = GPIO_REG_DDR_D;
    bit_offset = pin;
  } else if ((GPIO_PIN_8 <= pin)
             && (GPIO_PIN_13 >= pin)) {
    /* Port B */
    ddr_addr = GPIO_REG_DDR_B;
    bit_offset = pin - GPIO_PIN_8;
  } else if ((GPIO_PIN_A0 <= pin)
             && (GPIO_PIN_A5 >= pin)) {
    /* Analog pin (Port C) */
    ddr_addr = GPIO_REG_DDR_C;
    bit_offset = pin - GPIO_PIN_A0;
  }

  REGISTER_BIT_SET(ddr_addr, dir_mode, bit_offset);
}

void gpio_write(uint8_t pin, uint8_t val)
{
  uint8_t port_addr;
  uint8_t bit_offset;

  if ((GPIO_PIN_A5 < pin)
      || (GPIO_HIGH < val)) {
    return;
  }

  if ((GPIO_PIN_0 <= pin)
      && (GPIO_PIN_7 >= pin)) {
    /* Port D */
    port_addr = GPIO_REG_PORT_D;
    bit_offset = pin;
  } else if ((GPIO_PIN_8 <= pin)
             && (GPIO_PIN_13 >= pin)) {
    /* Port B */
    port_addr = GPIO_REG_PORT_B;
    bit_offset = pin - GPIO_PIN_8;
  } else if ((GPIO_PIN_A0 <= pin)
             && (GPIO_PIN_A5 >= pin)) {
    /* Analog pin (Port C) */
    port_addr = GPIO_REG_PORT_C;
    bit_offset = pin - GPIO_PIN_A0;
  }

  REGISTER_BIT_SET(port_addr, val, bit_offset);
}
