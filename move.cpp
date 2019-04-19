#include "move.h"
#include "Arduino.h"

/* Left motor set pins */
#define MOTOR_LEFT_EN_A   (10)  /* EnA pin for left motor set */
#define MOTOR_LEFT_IN_1   (13)  /* IN1 pin for left motor set */
#define MOTOR_LEFT_IN_2   (12)  /* IN2 pin for left motor set */
#define MOTOR_LEFT_EN_B   (9)   /* EnB pin for left motor set */
#define MOTOR_LEFT_IN_3   (11)  /* IN3 pin for left motor set */
#define MOTOR_LEFT_IN_4   (8)   /* IN4 pin for left motor set */

/* Right motor set pins */
#define MOTOR_RIGHT_EN_A  (6)   /* EnA pin for right motor set */
#define MOTOR_RIGHT_EN_B  (5)   /* EnB pin for right motor set */
#define MOTOR_RIGHT_IN_1  (7)   /* IN1 pin for right motor set */
#define MOTOR_RIGHT_IN_2  (4)   /* IN2 pin for right motor set */
#define MOTOR_RIGHT_IN_3  (3)   /* IN3 pin for right motor set */
#define MOTOR_RIGHT_IN_4  (2)   /* IN4 pin for right motor set */

void move_init()
{
  pinMode(MOTOR_LEFT_EN_A, OUTPUT);
  pinMode(MOTOR_LEFT_EN_B, OUTPUT);
  pinMode(MOTOR_LEFT_IN_1, OUTPUT);
  pinMode(MOTOR_LEFT_IN_2, OUTPUT);
  pinMode(MOTOR_LEFT_IN_3, OUTPUT);
  pinMode(MOTOR_LEFT_IN_4, OUTPUT);

  pinMode(MOTOR_RIGHT_EN_A, OUTPUT);
  pinMode(MOTOR_RIGHT_EN_B, OUTPUT);
  pinMode(MOTOR_RIGHT_IN_1, OUTPUT);
  pinMode(MOTOR_RIGHT_IN_2, OUTPUT);
  pinMode(MOTOR_RIGHT_IN_3, OUTPUT);
  pinMode(MOTOR_RIGHT_IN_4, OUTPUT);
}

void move_left()
{
  /* Stop left set of motors */
  digitalWrite(MOTOR_LEFT_IN_1, LOW);
  digitalWrite(MOTOR_LEFT_IN_3, LOW);
  digitalWrite(MOTOR_LEFT_IN_2, LOW);
  digitalWrite(MOTOR_LEFT_IN_4, LOW);

  /* Rotatate right set of motors */
  digitalWrite(MOTOR_RIGHT_IN_1, LOW);
  digitalWrite(MOTOR_RIGHT_IN_3, LOW);
  digitalWrite(MOTOR_RIGHT_IN_2, HIGH);
  digitalWrite(MOTOR_RIGHT_IN_4, HIGH);
}

void move_right()
{
  /* Stop right set of motors */
  digitalWrite(MOTOR_RIGHT_IN_1, LOW);
  digitalWrite(MOTOR_RIGHT_IN_3, LOW);
  digitalWrite(MOTOR_RIGHT_IN_2, LOW);
  digitalWrite(MOTOR_RIGHT_IN_4, LOW);

  /* Rotatate left set of motors */
  digitalWrite(MOTOR_LEFT_IN_1, LOW);
  digitalWrite(MOTOR_LEFT_IN_3, LOW);
  digitalWrite(MOTOR_LEFT_IN_2, HIGH);
  digitalWrite(MOTOR_LEFT_IN_4, HIGH);
}

void move_forward()
{
 /* Move A motors first */
  digitalWrite(MOTOR_LEFT_IN_1, LOW);
  digitalWrite(MOTOR_RIGHT_IN_1, LOW);
  digitalWrite(MOTOR_LEFT_IN_2, HIGH);
  digitalWrite(MOTOR_RIGHT_IN_2, HIGH);

  /* Move B motors second */
  digitalWrite(MOTOR_LEFT_IN_3, LOW);
  digitalWrite(MOTOR_RIGHT_IN_3, LOW);
  digitalWrite(MOTOR_LEFT_IN_4, HIGH);
  digitalWrite(MOTOR_RIGHT_IN_4, HIGH);
}

void move_backward()
{
 /* Move A motors first */
  digitalWrite(MOTOR_LEFT_IN_1, HIGH);
  digitalWrite(MOTOR_RIGHT_IN_1, HIGH);
  digitalWrite(MOTOR_LEFT_IN_2, LOW);
  digitalWrite(MOTOR_RIGHT_IN_2, LOW);

  /* Move B motors second */
  digitalWrite(MOTOR_LEFT_IN_3, HIGH);
  digitalWrite(MOTOR_RIGHT_IN_3, HIGH);
  digitalWrite(MOTOR_LEFT_IN_4, LOW);
  digitalWrite(MOTOR_RIGHT_IN_4, LOW);
}

void move_stop()
{
 /* Move A motors first */
  digitalWrite(MOTOR_LEFT_IN_1, LOW);
  digitalWrite(MOTOR_RIGHT_IN_1, LOW);
  digitalWrite(MOTOR_LEFT_IN_2, LOW);
  digitalWrite(MOTOR_RIGHT_IN_2, LOW);

  /* Move B motors second */
  digitalWrite(MOTOR_LEFT_IN_3, LOW);
  digitalWrite(MOTOR_RIGHT_IN_3, LOW);
  digitalWrite(MOTOR_LEFT_IN_4, LOW);
  digitalWrite(MOTOR_RIGHT_IN_4, LOW);
}
