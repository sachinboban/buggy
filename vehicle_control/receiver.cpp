#include "receiver.h"
#include "Arduino.h"

#define DEC_IN_PIN_0  (A2)
#define DEC_IN_PIN_1  (A3)
#define DEC_IN_PIN_2  (A4)
#define DEC_IN_PIN_3  (A5)

void receiver_init()
{
  pinMode(DEC_IN_PIN_0, INPUT);
  pinMode(DEC_IN_PIN_1, INPUT);
  pinMode(DEC_IN_PIN_2, INPUT);
  pinMode(DEC_IN_PIN_3, INPUT);
}

static int bin2dec(int b0, int b1)
{
  return ((b1 << 1) | b0);
}

void receiver_read(uint8_t *dir, int *spd)
{
  int d0_eval;
  int d1_eval;
  int d2_eval;
  int d3_eval;

  *dir = 0;
  *spd = 0;

  d0_eval = analogRead(DEC_IN_PIN_0);
  d1_eval = analogRead(DEC_IN_PIN_1);
  d2_eval = analogRead(DEC_IN_PIN_2);
  d3_eval = analogRead(DEC_IN_PIN_3);

  *dir = bin2dec(d0_eval, d1_eval);
  *spd = bin2dec(d2_eval, d3_eval);
}
