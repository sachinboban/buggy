#include "drive.h"
#include "motor.h"

#include "Arduino.h"

#define GEAR_0  (0) /* Gear 0 speed */
#define GEAR_1  (1) /* Gear 1 speed */
#define GEAR_2  (2) /* Gear 2 speed */
#define GEAR_3  (3) /* Gear 3 speed */

#define GEAR_0_SPEED  (0)   /* Gear 0 speed */
#define GEAR_1_SPEED  (150) /* Gear 1 speed */
#define GEAR_2_SPEED  (200) /* Gear 2 speed */
#define GEAR_3_SPEED  (255) /* Gear 3 speed */

void drive_init()
{
  int i;

  for(i = 0; i <= MTR_ID_R2; ++i) {
    /* Enable motors */
    motor_init(i);
  }
}

void drive_move(uint8_t dir, uint8_t spd)
{
  uint8_t mtr_spd;

  mtr_spd = GEAR_0_SPEED;

  if (GEAR_0 == spd) {
    mtr_spd = GEAR_0_SPEED;
  } else if (GEAR_1 == spd) {
    mtr_spd = GEAR_1_SPEED;
  } else if (GEAR_2 == spd) {
    mtr_spd = GEAR_2_SPEED;
  } else if (GEAR_3 == spd) {
    mtr_spd = GEAR_3_SPEED;
  }
  
  if (DRIVE_FWD == dir) {
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, mtr_spd);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_CLK, mtr_spd);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, mtr_spd);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_CLK, mtr_spd);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_BKWD == dir) {
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_ACLK, mtr_spd);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_ACLK, mtr_spd);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_ACLK, mtr_spd);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_ACLK, mtr_spd);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_LEFT == dir) {
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_ACLK, mtr_spd);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_CLK, mtr_spd);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_ACLK, mtr_spd);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_CLK, mtr_spd);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_RIGHT == dir) {
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, mtr_spd);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_ACLK, mtr_spd);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, mtr_spd);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_ACLK, mtr_spd);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_R2);
  }
}

void drive_stop()
{
  motor_stop(MTR_ID_L1);
  motor_stop(MTR_ID_R1);
  motor_stop(MTR_ID_L2);
  motor_stop(MTR_ID_R2);
}
