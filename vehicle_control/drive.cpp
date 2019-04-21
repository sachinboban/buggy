#include "drive.h"
#include "motor.h"

#include "Arduino.h"

#define TURN_SPEED  (150) /* Turning speed */
#define MOVE_SPEED  (200) /* Moving (fwd/bkwd) speed */

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
  if (DRIVE_FWD == dir) {
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, MOVE_SPEED);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_CLK, MOVE_SPEED);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, MOVE_SPEED);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_CLK, MOVE_SPEED);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_BKWD == dir) {
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_ACLK, MOVE_SPEED);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_ACLK, MOVE_SPEED);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_ACLK, MOVE_SPEED);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_ACLK, MOVE_SPEED);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_LEFT == dir) {
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_ACLK, TURN_SPEED);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_CLK, TURN_SPEED);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_ACLK, TURN_SPEED);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_CLK, TURN_SPEED);
    motor_rotate(MTR_ID_L1);
    motor_rotate(MTR_ID_L2);
    motor_rotate(MTR_ID_R1);
    motor_rotate(MTR_ID_R2);
  } else if (DRIVE_RIGHT == dir) {
    motor_configure(MTR_ID_L1, MTR_ROT_DIR_CLK, TURN_SPEED);
    motor_configure(MTR_ID_R1, MTR_ROT_DIR_ACLK, TURN_SPEED);
    motor_configure(MTR_ID_L2, MTR_ROT_DIR_CLK, TURN_SPEED);
    motor_configure(MTR_ID_R2, MTR_ROT_DIR_ACLK, TURN_SPEED);
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
