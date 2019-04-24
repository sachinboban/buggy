#include "transmit.h"
#include "gpio.h"
#include "Arduino.h"

#define ENC_PIN_0  (GPIO_PIN_9)
#define ENC_PIN_1  (GPIO_PIN_10)
#define ENC_PIN_2  (GPIO_PIN_11)
#define ENC_PIN_3  (GPIO_PIN_12)

void transmit_init()
{
  /* Initialize the required pins */
  gpio_set_mode(ENC_PIN_0, GPIO_PIN_DIR_OUTPUT);
  gpio_set_mode(ENC_PIN_1, GPIO_PIN_DIR_OUTPUT);
  gpio_set_mode(ENC_PIN_2, GPIO_PIN_DIR_OUTPUT);
  gpio_set_mode(ENC_PIN_3, GPIO_PIN_DIR_OUTPUT);
}

void transmit(uint8_t dir, int spd)
{
  int en0_val, en1_val, en2_val, en3_val;

  en0_val = LOW;
  en1_val = LOW;
  en2_val = LOW;
  en3_val = LOW;
  if (TRANS_DIR_FWD == dir) {
    en0_val = LOW;
    en1_val = LOW;
  } else if(TRANS_DIR_BKWD == dir) {
    en0_val = HIGH;
    en1_val = LOW;
  } else if(TRANS_DIR_LEFT == dir) {
    en0_val = LOW;
    en1_val = HIGH;
  } else if(TRANS_DIR_RIGHT == dir) {
    en0_val = HIGH;
    en1_val = HIGH;
  }

  if (0 == spd) {
    en2_val = LOW;
    en3_val = LOW;
  } else if(1 == spd) {
    en2_val = HIGH;
    en3_val = LOW;
  } else if(2 == spd) {
    en2_val = LOW;
    en3_val = HIGH;
  } else if(3 == spd) {
    en2_val = HIGH;
    en3_val = HIGH;
  }

  Serial.print(en3_val);
  Serial.print(", ");
  Serial.print(en2_val);
  Serial.print(", ");
  Serial.print(en1_val);
  Serial.print(", ");
  Serial.print(en0_val);
  Serial.print("\n");

  gpio_write(ENC_PIN_0,en0_val);
  gpio_write(ENC_PIN_1,en1_val);
  gpio_write(ENC_PIN_2,en2_val);
  gpio_write(ENC_PIN_3,en3_val);
}
