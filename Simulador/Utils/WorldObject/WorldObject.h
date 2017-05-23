#ifndef WORLD_OBJECT_H_
#define  WORLD_OBJECT_H_

enum WorldObjects {
    BALL,
    GOAL,
    OPPONENT,
    TEAMMATE
};

typedef struct world_object {
    int objId;
    double posX, posY;
} world_object_t;

#endif
