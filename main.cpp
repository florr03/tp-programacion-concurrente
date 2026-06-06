#include <iostream>
#include <thread>

#include "productor.h"
#include "worker.h"
#include "vram_pool.h"
#include "messagequeue.h"


// Buffer 1 - MessageQueue con prioridad y anti-starvation
MessageQueue messageQueue;

int main()
{
    initVRAM();

    // Productor
    std::thread t_prod(productor,1);
    std::thread t_prod2(productor,2);

    // Workers
    std::thread w1(worker, 1);
    std::thread w2(worker, 2);
    std::thread w3(worker, 3);

    t_prod.join();
    t_prod2.join();
    w1.join();
    w2.join();
    w3.join();

    return 0;
}
