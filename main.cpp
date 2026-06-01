#include <iostream>
#include <thread>
#include <queue>
#include <mutex>

#include "productor.h"
#include "worker.h"
#include "vram_pool.h"
#include "semaforo.h"

// Cola compartida (Buffer 1 - Message Queue)
std::queue<Job> messageQueue;

// Semaforos productor-consumidor
Semaforo hay_espacio;
Semaforo hay_datos;

// Mutex de la cola
std::mutex mtx_queue;

int main()
{
    init(hay_espacio, 10);
    init(hay_datos, 0);

    initVRAM();

    // Productor
    std::thread t_prod(productor);

    // Workers
    std::thread w1(worker, 1);
    std::thread w2(worker, 2);
    std::thread w3(worker, 3);

    t_prod.join();
    w1.join();
    w2.join();
    w3.join();

    return 0;
}
