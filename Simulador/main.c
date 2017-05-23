#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./Utils/Accelerometer/Accelerometer.h"
#include "./Utils/Vision/Vision.h"

// TODO: Definir onde a variável bola será usada (provavelmente aqui).

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    vision_t testarVisao = readInfoFromCamera();
    accelerometer_t testarAcc = readInfoFromAcelerometer();

    printf("Informações do acelerômetro:\n");
    printf("Aceleração em X: %lf\n", testarAcc.accelerationX);
    printf("Aceleração em Y: %lf\n", testarAcc.accelerationY);
    printf("Aceleração em Z: %lf\n", testarAcc.accelerationZ);

    // TODO: Criação das threads dos agentes.

    return 0;
}
