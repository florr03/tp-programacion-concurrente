#ifndef PRODUCTOR_H
#define PRODUCTOR_H


struct Job {
    int id = 0;
    int prioridad;
};

void productor();
void consumidor();
void cargarJob(Job& j);

#endif
