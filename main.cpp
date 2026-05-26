#include <iostream>
#include <thread>
#include <queue>

#include "worker.h"
#include "vram_pool.h"
#include "semaforo.h"

std::queue<Job> messageQueue;

Semaforo hay_jobs;

std::mutex mtx_queue;

int main() {

    init(hay_jobs, 0);

    initVRAM();

    // ===================================
    // Jobs de prueba
    // ===================================

    for (int i = 1; i <= 8; i++) {

        Job j;

        j.id = i;

        j.prioridad = 1;

        messageQueue.push(j);

        signal(hay_jobs);
    }

    // ===================================
    // Workers
    // ===================================

    std::thread w1(worker, 1);
    std::thread w2(worker, 2);
    std::thread w3(worker, 3);

    w1.join();
    w2.join();
    w3.join();

    return 0;
}