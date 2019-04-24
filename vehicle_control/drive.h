#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"

#define DRIVE_FWD   (0) /* Drive forward (+Y axis) */
#define DRIVE_BKWD  (1) /* Drive backward (-Y axis) */
#define DRIVE_LEFT  (2) /* Drive left (-X axis) */
#define DRIVE_RIGHT (3) /* Drive right (+X axis) */

#define GEAR_0  (0) /* Gear 0 */
#define GEAR_1  (1) /* Gear 1 */
#define GEAR_2  (2) /* Gear 2 */
#define GEAR_3  (3) /* Gear 3 */

/*
 * @brief Initialize the drive system
 */
void drive_init();

/*
 * @brief Move in the Y axis with the given speed
 *
 * @dir     Direction of movement
 * @gear    Gear
 * @sub_dir Sub-direction used while turning left or right
 */
void drive_move(uint8_t dir, uint8_t gear, uint8_t sub_dir);

/*
 * @brief Stop the vehicile
 */
void drive_stop();

#endif  /* DRIVE_H */
