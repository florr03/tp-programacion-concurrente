#ifndef VRAM_POOL_H
#define VRAM_POOL_H

#include <queue>
#include <mutex>
#include "job.h"
#include "semaforo.h"

// Buffer 2: Una cola clásica compartida
extern std::queue<Job> poolVRAM;
extern std::mutex mtx_vram;
extern Semaforo slots_vram;

void initVRAM();

#endif
