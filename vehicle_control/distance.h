#ifndef DIST_H
#define DIST_H

/*
 * @brief Initialize the pins
 */
void distance_init();

/*
 * @brief Get the distance (in cm) to the obstacle in front
 */
int get_distance_cm();

#endif  /* DIST_H */
