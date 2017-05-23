#ifndef AGENT_H_
#define  AGENT_H_

/* Cada agente tem um conjunto de sensores (/Utils/Accelerometer e /Utils/Vision) e atuadores
(posicionamento e de comunicação (através de mensagens entre agentes)).
*/

/* Definitions */
typedef struct sensors_info {
    accelerometer_t accelerometer;
    vision_t vision;
    hearing_t hearing; // Para comunicação!
} sensors_t;

// TODO: Implementar atuadores.
// typedef struct effectors_info {
//     // beam_t e say_t (PROVAVELMENTE)
// } effectors_t;

/* Functions */
sensors_t readSensors();
// void sendInfoToCentral();
// void think();
// void act();

#endif
