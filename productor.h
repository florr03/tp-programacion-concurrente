#ifndef PRODUCTOR_H
#define PRODUCTOR_H

#include "job.h"

void productor(int id_productor);

//void consumidor(); -> no se utiliza
void cargarJob(Job& j);

#endif
