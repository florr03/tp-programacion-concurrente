#ifndef VRAM_POOL_H
#define VRAM_POOL_H

#include <vector>
#include <mutex>
#include "semaforo.h"
#include "job.h"

extern std::vector<Job> poolVRAM;

extern std::mutex mtx_vram;

extern Semaforo slots_vram;

void initVRAM();

#endif
