#ifndef RECV_H
#define RECV_H

#include "Arduino.h"

/*
 * @brief Initialize the receiver
 */
void receiver_init();

/*
 * @brief Receive the direction and speed
 * 
 * @dir Pointer to store received direction
 * @spd Pointer to store received speed
 */
void receiver_read(uint8_t *dir, int *spd);

#endif  /* RECV_H */
