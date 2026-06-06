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


    // Workers
    std::thread w1(worker, 1);
    std::thread w2(worker, 2);


    t_prod.join();

    w1.join();
    w2.join();


    return 0;
}
