#ifndef MOTOR_H
#define MOTOR_H

#define MTR_SET_L (0) /* Motor set left */ 
#define MTR_SET_R (1) /* Motor set right */

#define MTR_SET_ROT_ACLK  (0) /* Anti-clockwise direction */ 
#define MTR_SET_ROT_CLK   (1) /* Clockwise direction */

/*
 * @brief Initialize all the motor sets.
 */
void motor_init();

/*
 * @brief   Configure the motor set.
 *
 * @set_id  Motor set ID (MTR_SET_x)
 * @dir     Direction of rotation (MTR_SET_ROT_xxxx)
 * @spd     Rotation speed
 */
void motor_configure(int set_id, int dir, int spd);

/*
 * @brief   Rotate the given motor set with the most
 *          recent configuration.
 *
 * @set_id  Motor set ID (MTR_SET_x)
 */
void motor_rotate(int set_id);

/*
 * @brief   Stop all motor sets.
 */
void motor_stop_all();

#endif  /* MOTOR_H */
