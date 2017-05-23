#include "Agent.h"
#include "/Utils/Vision/Vision.h"
#include "/Utils/Accelerometer/Accelerometer.h"

sensors_t sensors;

/* Functions */
sensors_t readSensors() {
    // Ler da visão
    sensors.vision = readInfoFromCamera();

    // Ler do acelerômetro
    sensors.accelerometer = readInfoFromAcelerometer();

    // Ouvir mensagens
    sensors.hearing = listenFromHearing();

    return sensors
}
// TODO: Implementar métodos dos agentes.
// void sendInfoToCentral() {}
// void think() {}
// void act() {}
