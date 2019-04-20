#include "motor.h"
#include "Arduino.h"

struct motor_cfg {
  int dir;
  int spd;
} cfg[2];

/* Left motor set pins */
#define MTR_SET_L_EN_A  (10)  /* EnA pin for left motor set */
#define MTR_SET_L_IN_1  (13)  /* IN1 pin for left motor set */
#define MTR_SET_L_IN_2  (12)  /* IN2 pin for left motor set */
#define MTR_SET_L_EN_B  (9)   /* EnB pin for left motor set */
#define MTR_SET_L_IN_3  (11)  /* IN3 pin for left motor set */
#define MTR_SET_L_IN_4  (8)   /* IN4 pin for left motor set */

/* Right motor set pins */
#define MTR_SET_R_EN_A  (6)   /* EnA pin for right motor set */
#define MTR_SET_R_EN_B  (5)   /* EnB pin for right motor set */
#define MTR_SET_R_IN_1  (7)   /* IN1 pin for right motor set */
#define MTR_SET_R_IN_2  (4)   /* IN2 pin for right motor set */
#define MTR_SET_R_IN_3  (3)   /* IN3 pin for right motor set */
#define MTR_SET_R_IN_4  (2)   /* IN4 pin for right motor set */

static void set_motor_pin_direction()
{
  pinMode(MTR_SET_L_EN_A, OUTPUT);
  pinMode(MTR_SET_L_IN_1, OUTPUT);
  pinMode(MTR_SET_L_IN_2, OUTPUT);
  pinMode(MTR_SET_L_EN_B, OUTPUT);
  pinMode(MTR_SET_L_IN_3, OUTPUT);
  pinMode(MTR_SET_L_IN_4, OUTPUT);

  pinMode(MTR_SET_R_EN_A, OUTPUT);
  pinMode(MTR_SET_R_IN_1, OUTPUT);
  pinMode(MTR_SET_R_IN_2, OUTPUT);
  pinMode(MTR_SET_R_EN_B, OUTPUT);
  pinMode(MTR_SET_R_IN_3, OUTPUT);
  pinMode(MTR_SET_R_IN_4, OUTPUT);
}

void motor_stop_all()
{
  /* Stop A motors first */
  analogWrite(MTR_SET_L_EN_A, 0);
  analogWrite(MTR_SET_R_EN_A, 0);
  digitalWrite(MTR_SET_L_IN_1, LOW);
  digitalWrite(MTR_SET_R_IN_1, LOW);
  digitalWrite(MTR_SET_L_IN_2, LOW);
  digitalWrite(MTR_SET_R_IN_2, LOW);

  /* Stop B motors second */
  analogWrite(MTR_SET_L_EN_B, 0);
  analogWrite(MTR_SET_R_EN_B, 0);
  digitalWrite(MTR_SET_L_IN_3, LOW);
  digitalWrite(MTR_SET_R_IN_3, LOW);
  digitalWrite(MTR_SET_L_IN_4, LOW);
  digitalWrite(MTR_SET_R_IN_4, LOW);

//  cfg[MTR_SET_L].dir = MTR_SET_ROT_CLK;
//  cfg[MTR_SET_L].spd = 0;
 //  cfg[MTR_SET_R].spd = 0;
}

void motor_init()
{
  /* Put all the pins to output */
  set_motor_pin_direction();

  /* Stop all motors */
  motor_stop_all();

  cfg[MTR_SET_L].dir = MTR_SET_ROT_CLK;
  cfg[MTR_SET_L].spd = 0;
  cfg[MTR_SET_R].dir = MTR_SET_ROT_CLK;
  cfg[MTR_SET_R].spd = 0;
}

void motor_configure(int set_id, int dir, int spd)
{
  if (MTR_SET_L == set_id) {
    cfg[MTR_SET_L].dir = dir;
    cfg[MTR_SET_L].spd = spd;
  } else {
    cfg[MTR_SET_R].dir = dir;
    cfg[MTR_SET_R].spd = spd;
  }
}

void motor_rotate(int set_id)
{
  if (MTR_SET_L == set_id) {
    analogWrite(MTR_SET_L_EN_A, cfg[MTR_SET_L].spd);
    analogWrite(MTR_SET_L_EN_B, cfg[MTR_SET_L].spd);
    if(MTR_SET_ROT_CLK == cfg[MTR_SET_L].dir) { 
      digitalWrite(MTR_SET_L_IN_1, LOW);
      digitalWrite(MTR_SET_L_IN_3, LOW);
      digitalWrite(MTR_SET_L_IN_2, HIGH);
      digitalWrite(MTR_SET_L_IN_4, HIGH);
    } else {
      digitalWrite(MTR_SET_L_IN_1, HIGH);
      digitalWrite(MTR_SET_L_IN_3, HIGH);
      digitalWrite(MTR_SET_L_IN_2, LOW);
      digitalWrite(MTR_SET_L_IN_4, LOW);
    }
  } else if (MTR_SET_R == set_id) {
    analogWrite(MTR_SET_R_EN_A, cfg[MTR_SET_R].spd);
    analogWrite(MTR_SET_R_EN_B, cfg[MTR_SET_R].spd);
    if(MTR_SET_ROT_CLK == cfg[MTR_SET_R].dir) { 
      digitalWrite(MTR_SET_R_IN_1, LOW);
      digitalWrite(MTR_SET_R_IN_3, LOW);
      digitalWrite(MTR_SET_R_IN_2, HIGH);
      digitalWrite(MTR_SET_R_IN_4, HIGH);
    } else {
      digitalWrite(MTR_SET_R_IN_1, HIGH);
      digitalWrite(MTR_SET_R_IN_3, HIGH);
      digitalWrite(MTR_SET_R_IN_2, LOW);
      digitalWrite(MTR_SET_R_IN_4, LOW);
    }
  } else {
    Serial.print("motor_rotate: Invalid set_id\n");
  }
}
