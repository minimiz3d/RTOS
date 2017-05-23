#include "Vision.h"

vision_t readInfoFromCamera() {
    // Gera-se 'n' objetos no campo de visão
    int n = randomNumber(1,4);

    vision_t currentVision;
    currentVision.angleX = randomNumber(0,100);
    currentVision.angleY = randomNumber(0,100);
    currentVision.distance = randomNumber(0,10);
    currentVision.wObject = (world_object_t *) calloc(n, sizeof(world_object_t));

    // Definição de objetos vistos
    for (size_t i = 0; i < n; i++) {
        // currentVision.wObject = (world_object_t *) malloc(sizeof(world_object_t));
        currentVision.wObject[i].objId = i;
        currentVision.wObject[i].posX = randomNumber(0,10);
        currentVision.wObject[i].posY = randomNumber(0,10);
    }

    for (size_t i = 0; i < n; i++) {
        printf("Objeto de mundo %d:\n", i);
        char *objName = getWorldObjectName(currentVision.wObject[i].objId);
        printf("Tipo: %s\n", objName);
        printf("posX: %lf\n", (double)currentVision.wObject[i].posX);
        printf("posY: %lf\n\n", (double)currentVision.wObject[i].posY);
    }

    return currentVision;
}
