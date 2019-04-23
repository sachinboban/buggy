#include "motor.h"
#include "gpio.h"
#include "Arduino.h"

/*
 * Pins connected to the L298N
 *
 * NOTE: L298N_L denotes the L298N controlling
 * the motors on the left, while L298N_R denotes
 * the L298N controlling the motors on the right
 */
#define L298N_L_EN_B  (GPIO_PIN_9)
#define L298N_L_IN_3  (GPIO_PIN_11)
#define L298N_L_IN_4  (GPIO_PIN_8)

#define L298N_L_EN_A  (GPIO_PIN_10)
#define L298N_L_IN_1  (GPIO_PIN_13)
#define L298N_L_IN_2  (GPIO_PIN_12)

#define L298N_R_EN_A  (GPIO_PIN_6)
#define L298N_R_IN_1  (GPIO_PIN_7)
#define L298N_R_IN_2  (GPIO_PIN_4)

#define L298N_R_EN_B  (GPIO_PIN_5)
#define L298N_R_IN_3  (GPIO_PIN_3)
#define L298N_R_IN_4  (GPIO_PIN_2)

/* Pins controlling motor L1 */
#define MTR_L1_SPEED_PIN  L298N_L_EN_B
#define MTR_L1_DIR_PIN_1  L298N_L_IN_4
#define MTR_L1_DIR_PIN_2  L298N_L_IN_3

/* Pins controlling motor L2 */
#define MTR_L2_SPEED_PIN  L298N_L_EN_A
#define MTR_L2_DIR_PIN_1  L298N_L_IN_2
#define MTR_L2_DIR_PIN_2  L298N_L_IN_1

/* Pins controlling motor R1 */
#define MTR_R1_SPEED_PIN  L298N_R_EN_A
#define MTR_R1_DIR_PIN_1  L298N_R_IN_2
#define MTR_R1_DIR_PIN_2  L298N_R_IN_1

/* Pins controlling motor R2 */
#define MTR_R2_SPEED_PIN  L298N_R_EN_B
#define MTR_R2_DIR_PIN_1  L298N_R_IN_4
#define MTR_R2_DIR_PIN_2  L298N_R_IN_3

typedef struct {
  int speed_pin;
  int dir_pin1;
  int dir_pin2;
} pin_map_t;

static const pin_map_t mtr_pin_map[4] = {
  {
    MTR_L1_SPEED_PIN,
    MTR_L1_DIR_PIN_1,
    MTR_L1_DIR_PIN_2,
  },
  {
    MTR_L2_SPEED_PIN,
    MTR_L2_DIR_PIN_1,
    MTR_L2_DIR_PIN_2,
  },
  {
    MTR_R1_SPEED_PIN,
    MTR_R1_DIR_PIN_1,
    MTR_R1_DIR_PIN_2,
  },
  {
    MTR_R2_SPEED_PIN,
    MTR_R2_DIR_PIN_1,
    MTR_R2_DIR_PIN_2,
  }
};

typedef struct {
  int8_t dir;
  uint8_t spd;
} motor_cfg_t;

/* Configuration of each motor */
static motor_cfg_t mtr_cfg[4];

void motor_stop(uint8_t id)
{
  if (MTR_ID_R2 >= id) {
    analogWrite(mtr_pin_map[id].speed_pin, 0);
    digitalWrite(mtr_pin_map[id].dir_pin1, LOW);
    digitalWrite(mtr_pin_map[id].dir_pin2, LOW);
  } else {
    Serial.print("motor_configure: Invalid motor id\n");
    return;
  }
}

void motor_init(uint8_t id)
{
  if (MTR_ID_R2 >= id) {
    /* Set pin direction */
    gpio_set_mode(mtr_pin_map[id].speed_pin, GPIO_PIN_DIR_OUTPUT);
    gpio_set_mode(mtr_pin_map[id].dir_pin1, GPIO_PIN_DIR_OUTPUT);
    gpio_set_mode(mtr_pin_map[id].dir_pin2, GPIO_PIN_DIR_OUTPUT);
  
    /* Stop motor */
    motor_stop(id);
  
    /* Initialize motor configuration structure */
    mtr_cfg[id].dir = MTR_ROT_DIR_CLK;
    mtr_cfg[id].spd = 0;
  } else {
    Serial.print("motor_init: Invalid motor id\n");
  }
}

void motor_configure(uint8_t id, int8_t dir, uint8_t spd)
{
  if (MTR_ID_R2 >= id) {
    mtr_cfg[id].dir = dir;
    mtr_cfg[id].spd = spd;
  } else {
    Serial.print("motor_configure: Invalid motor id\n");
  }
}

void motor_rotate(uint8_t id)
{
  if (MTR_ID_R2 >= id) {    
    analogWrite(mtr_pin_map[id].speed_pin, mtr_cfg[id].spd);

    if (MTR_ROT_DIR_CLK == mtr_cfg[id].dir) {
      digitalWrite(mtr_pin_map[id].dir_pin1, HIGH);
      digitalWrite(mtr_pin_map[id].dir_pin2, LOW);
    } else {
      digitalWrite(mtr_pin_map[id].dir_pin1, LOW);
      digitalWrite(mtr_pin_map[id].dir_pin2, HIGH);
    }
  } else {
    Serial.print("motor_configure: Invalid motor id\n");
    return;
  }
}
