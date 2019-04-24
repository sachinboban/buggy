#include "drive.h"
#include "motor.h"

#include "Arduino.h"

#define TURN_GEAR (GEAR_1)

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

static uint8_t gear2speed(uint8_t gear)
{
  uint8_t spd;

  spd = GEAR_0_SPEED;

  if (GEAR_0 == gear) {
    spd = GEAR_0_SPEED;
  } else if (GEAR_1 == gear) {
    spd = GEAR_1_SPEED;
  } else if (GEAR_2 == gear) {
    spd = GEAR_2_SPEED;
  } else if (GEAR_3 == gear) {
    spd = GEAR_3_SPEED;
  }

  return spd;
}

void drive_move(uint8_t dir, uint8_t gear, uint8_t sub_dir)
{
  uint8_t spd;
  uint8_t turn_speed;
  uint8_t mtr_left_rot;
  uint8_t mtr_right_rot;

  spd = GEAR_0_SPEED;
  
  if (DRIVE_FWD == dir) {
    spd = gear2speed(gear);
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, spd);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_CLK, spd);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, spd);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_CLK, spd);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_BKWD == dir) {
    spd = gear2speed(gear);
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_ACLK, spd);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_ACLK, spd);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_ACLK, spd);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_ACLK, spd);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_LEFT == dir) {
    
    /* Set the rotation directions */
    mtr_left_rot = MTR_ROT_DIR_ACLK;
    mtr_right_rot = MTR_ROT_DIR_CLK;

    if (gear != GEAR_0) {
      if (DRIVE_FWD == sub_dir) {
        mtr_left_rot = MTR_ROT_DIR_CLK;
        mtr_right_rot = MTR_ROT_DIR_CLK;
      } else {
        mtr_left_rot = MTR_ROT_DIR_ACLK;
        mtr_right_rot = MTR_ROT_DIR_ACLK;
      }
    }

    /* Get the motor speeds */
    turn_speed = gear2speed(TURN_GEAR);

    if (gear != GEAR_0) {
      gear += (2 * TURN_GEAR);
      if (gear > GEAR_3)
        gear = GEAR_3;
    } else {
      gear = TURN_GEAR;
    }
    spd = gear2speed(gear);
    
    motor_configure(MTR_ID_L1, mtr_left_rot, turn_speed);
    motor_configure(MTR_ID_R1, mtr_right_rot, spd);
    motor_configure(MTR_ID_L2, mtr_left_rot, turn_speed);
    motor_configure(MTR_ID_R2, mtr_right_rot, spd);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_RIGHT == dir) {
    /* Set the rotation directions */
    mtr_left_rot = MTR_ROT_DIR_CLK;
    mtr_right_rot = MTR_ROT_DIR_ACLK;

    if (gear != GEAR_0) {
      if (DRIVE_FWD == sub_dir) {
        mtr_left_rot = MTR_ROT_DIR_CLK;
        mtr_right_rot = MTR_ROT_DIR_CLK;
      } else {
        mtr_left_rot = MTR_ROT_DIR_ACLK;
        mtr_right_rot = MTR_ROT_DIR_ACLK;
      }
    }

    /* Get the motor speeds */
    turn_speed = gear2speed(TURN_GEAR);

    if (gear != GEAR_0) {
      gear += (2 * TURN_GEAR);
      if (gear > GEAR_3)
        gear = GEAR_3;
    } else {
      gear = TURN_GEAR;
    }
    spd = gear2speed(gear);

    motor_configure(MTR_ID_L1, mtr_left_rot, spd);
    motor_configure(MTR_ID_R1, mtr_right_rot, turn_speed);
    motor_configure(MTR_ID_L2, mtr_left_rot, spd);
    motor_configure(MTR_ID_R2, mtr_right_rot, turn_speed);
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
