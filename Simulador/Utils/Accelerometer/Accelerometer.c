#include "Accelerometer.h"

accelerometer_t readInfoFromAcelerometer() {
    // Gerar valores para as acelerações
    accelerometer_t currentAccelerations;

    // TODO: definir valores máximos e mínimos de aceleração para cada eixo
    currentAccelerations.accelerationX = (double)randomNumber(0,10);
    currentAccelerations.accelerationY = (double)randomNumber(0,10);
    currentAccelerations.accelerationZ = (double)randomNumber(0,10);

    return currentAccelerations;
}
