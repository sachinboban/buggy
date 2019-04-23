#ifndef TRANSMIT_H
#define TRANSMIT_H

#include "Arduino.h"

/* Movement to be transmitted */
#define TRANS_DIR_FWD   (0) /* Forward (+Y) */
#define TRANS_DIR_BKWD  (1) /* Backward (-Y) */
#define TRANS_DIR_LEFT  (2) /* Left (-X) */
#define TRANS_DIR_RIGHT (3) /* Right (+X) */

/*
 * @brief Initialize the transmition unit
 */
void transmit_init();

/*
 * @brief Transmit the direction and speed to vehicle
 *
 * @dir Direction of movement (TRANS_DIR_xxxx)
 * @spd Speed to be sent to the vehicle (maximum of 1023)
 */
void transmit(uint8_t dir, int spd);

#endif  /* TRANSMIT_H */
