#include "motor.h"
#include "Arduino.h"

/*
 * Pins connected to the L298N
 *
 * NOTE: L298N_L denotes the L298N controlling
 * the motors on the left, while L298N_R denotes
 * the L298N controlling the motors on the right
 */
#define L298N_L_EN_B  (3)
#define L298N_L_IN_3  (2)
#define L298N_L_IN_4  (4)

#define L298N_L_EN_A  (11)
#define L298N_L_IN_1  (12)
#define L298N_L_IN_2  (13)

#define L298N_R_EN_A  (10)
#define L298N_R_IN_1  (9)
#define L298N_R_IN_2  (8)

#define L298N_R_EN_B  (5)
#define L298N_R_IN_3  (6)
#define L298N_R_IN_4  (7)

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

static void mtr_print_cfg_info(uint8_t id, int8_t dir, uint8_t spd)
{
  Serial.print("[mtr(");
  if (MTR_ID_L1 == id)
    Serial.print("FL)]");
  else if (MTR_ID_L2 == id)
    Serial.print("BL)]");
  else if (MTR_ID_R1 == id)
    Serial.print("FR)]");
  else if (MTR_ID_R2 == id)
    Serial.print("BR)]");

  Serial.print("[speed(");
  Serial.print(spd);

  Serial.print(")][dir(");
  if (MTR_ROT_DIR_CLK == dir)
    Serial.print("CLK)]\n");
  else
    Serial.print("ACLK)]\n");
}

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
    pinMode(mtr_pin_map[id].speed_pin, OUTPUT);
    pinMode(mtr_pin_map[id].dir_pin1, OUTPUT);
    pinMode(mtr_pin_map[id].dir_pin2, OUTPUT);
    Serial.print("***begin init***\n");
    Serial.print(id);
    Serial.print(", ");
    Serial.print(mtr_pin_map[id].speed_pin);
    Serial.print(", ");
    Serial.print(mtr_pin_map[id].dir_pin1);
    Serial.print(", ");
    Serial.print(mtr_pin_map[id].dir_pin2);
    Serial.print("***end init***\n");
  
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
    
    Serial.print("[CONFIG]");
    mtr_print_cfg_info(id, mtr_cfg[id].dir, mtr_cfg[id].spd);
  } else {
    Serial.print("motor_configure: Invalid motor id\n");
  }
}

void motor_rotate(uint8_t id)
{
  if (MTR_ID_R2 >= id) {
    Serial.print("[ROT]");
    mtr_print_cfg_info(id, mtr_cfg[id].dir, mtr_cfg[id].spd);
    
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
