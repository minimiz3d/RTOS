#include "GenericUtils.h"
#include "./WorldObject/WorldObject.h"

/* Generating random numbers */
int randomNumber(int min, int max) {
    int r = (rand() % max) + min;
    return r;
}

/* Acess to enum name through key */
const char* getWorldObjectName(enum WorldObjects worldObject)  {
   switch (worldObject) {
      case BALL: return "Ball";
      case GOAL: return "Goal";
      case OPPONENT: return "Opponent";
      default: return "TeamMate";
   }
}
