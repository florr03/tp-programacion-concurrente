#ifndef JOB_H
#define JOB_H

#include "estado.h"

struct Job {
    int id = 0;
    int prioridad;
    Estado estado = CREADO;
};

#endif
