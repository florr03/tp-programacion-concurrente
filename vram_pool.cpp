#include "vram_pool.h"

std::vector<Job> poolVRAM;

std::mutex mtx_vram;

Semaforo slots_vram;

void initVRAM() {

    init(slots_vram, 5);

}