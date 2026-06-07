#ifndef JOB_H
#define JOB_H

#include "estado.h"
#include <ctime>

struct Job {
    int id = 0;
    int prioridad; // 0 = Free, 1 = Premium
    Estado estado = CREADO;
};

#endif
