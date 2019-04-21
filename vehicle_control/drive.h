#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"

#define DRIVE_FWD   (0) /* Drive forward (+Y axis) */
#define DRIVE_BKWD  (1) /* Drive backward (-Y axis) */
#define DRIVE_LEFT  (2) /* Drive left (-X axis) */
#define DRIVE_RIGHT (3) /* Drive right (+X axis) */

/*
 * @brief Initialize the drive system
 */
void drive_init();

/*
 * @brief Move in the Y axis with the given speed
 *
 * @dir Direction of movement
 * @spd Speed
 */
void drive_move(uint8_t dir, uint8_t spd);

/*
 * @brief Stop the vehicile
 */
void drive_stop();

#endif  /* DRIVE_H */
