#include "vram_pool.h"

std::queue<Job> poolVRAM;
std::mutex mtx_vram;
Semaforo slots_vram;

void initVRAM() {
    init(slots_vram, 5); // Arranca el semaforo con los 5 slots libres
}
