#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include "job.h"

// MessageQueue (Buffer 1 de la consigna): cola con prioridad
// Premium/Free y politica anti-starvation por aging.
class MessageQueue {
public:
    void push(Job j);
    Job extraer();

private:
    struct Entrada {
        Job job;
        std::chrono::high_resolution_clock::time_point tiempoEncolado;
    };

    std::queue<Entrada> colaPremium;
    std::queue<Entrada> colaFree;

    std::mutex mtx;
    std::condition_variable cv;
};

#endif
