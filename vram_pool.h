#ifndef VRAM_POOL_H
#define VRAM_POOL_H

#include <vector>
#include <mutex>
#include "semaforo.h"

struct Job {

    int id;
    int prioridad;

};

extern std::vector<Job> poolVRAM;

extern std::mutex mtx_vram;

extern Semaforo slots_vram;

void initVRAM();

#endif