#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

#define MTR_ID_L1 (0) /* Motor L1 */
#define MTR_ID_L2 (1) /* Motor L2 */
#define MTR_ID_R1 (2) /* Motor R1 */
#define MTR_ID_R2 (3) /* Motor R1 */

#define MTR_ROT_DIR_CLK   (1) /* Clockwise rotation */
#define MTR_ROT_DIR_ACLK  (2) /* Anti-clockwise rotation */

/*
 * @brief Initialize the given motor
 *
 * @id  Motor ID (MTR_ID_xx)
 */
void motor_init(uint8_t id);

/*
 * @brief Configure the given motor
 *
 * @id  Motor ID (MTR_ID_xx)
 * @dir Direction of rotation (MTR_ROT_DIR_xxxx)
 * @spd Rotation speed
 */
void motor_configure(uint8_t id, int8_t dir, uint8_t spd);

/*
 * @brief Rotate the given motor
 *
 * Rotate the given motor as per the most recent configuration
 *
 * @id  Motor ID (MTR_ID_xx)
 */
void motor_rotate(uint8_t id);

/*
 * @brief Stop the given motor
 *
 * NOTE: This API does not change the recent configuration
 *
 * @id  Motor ID (MTR_ID_xx)
 */
void motor_stop(uint8_t id);

#endif  /* MOTOR_H */
