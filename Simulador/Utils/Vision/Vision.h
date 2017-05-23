#ifndef VISON_H_
#define VISION_H_

#include "../GenericUtils.h"
#include "../WorldObject/WorldObject.h"

/* Definitions */
typedef struct vision_info {
    world_object_t *wObject;
    double angleX, angleY;  // 0 < angleX,Y < 100 deg
    double distance;        // 0.1 < distance < 10m
} vision_t;

/* Functions */
vision_t readInfoFromCamera();

#endif
