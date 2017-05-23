#ifndef VISON_H_
#define VISION_H_

#include "../GenericUtils.h"

/* Definitions */
typedef struct accelerometer_info {
    double accelerationX;    // m/s²
    double accelerationY;    // m/s²
    double accelerationZ;    // m/s²
} accelerometer_t;

/* Functions */
accelerometer_t readInfoFromAcelerometer();

#endif
