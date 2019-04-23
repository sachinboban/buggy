#include "distance.h"
#include "gpio.h"
#include "Arduino.h"

#define HC_SRO4_TRIG_PIN  (GPIO_PIN_15)
#define HC_SRO4_ECHO_PIN  (GPIO_PIN_14)

void distance_init()
{
  gpio_set_mode(HC_SRO4_TRIG_PIN, GPIO_PIN_DIR_OUTPUT);
  gpio_set_mode(HC_SRO4_ECHO_PIN, GPIO_PIN_DIR_INPUT);
}

int get_distance_cm()
{
  long duration;
  int dist_cm;

  /* Clear the trigger pin for 2 microseconds */
  digitalWrite(HC_SRO4_TRIG_PIN, LOW);
  delayMicroseconds(2);

  /*
   * Generate Ultra sound wave by setting trigger pin
   * to high for 10 micro seconds.
   */
  digitalWrite(HC_SRO4_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_SRO4_TRIG_PIN, LOW);

  /* Measure duration for echo pin to turn high */
  duration = pulseIn(HC_SRO4_ECHO_PIN, HIGH);
  dist_cm = (duration * 0.034) / 2;

  return dist_cm;
}
