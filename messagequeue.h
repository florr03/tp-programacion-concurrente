#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "job.h"

struct Entrada {
    Job job;
    std::time_t tiempoEncolado; // Registra el segundo exacto en que ingresó
};

struct MessageQueue {
    std::queue<Entrada> colaPremium;
    std::queue<Entrada> colaFree;
    std::mutex mtx;
    std::condition_variable cv;
};

// Funciones sueltas globales (Estilo de la materia)
void push(MessageQueue& mq, Job j);
Job extraer(MessageQueue& mq);

#endif
