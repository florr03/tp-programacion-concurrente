#include "worker.h"
#include "vram_pool.h"
#include "semaforo.h"
#include "messagequeue.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

// Cola compartida (Buffer 1)
extern MessageQueue messageQueue;

void worker(int id_worker) {

    while (true) {

        // ===================================
        // Espera (pasiva) y extrae job de la cola
        // ===================================

        Job job = messageQueue.extraer();

        // ===================================
        // Espera slot libre en VRAM
        // ===================================

        wait(slots_vram);

        // ===================================
        // Asignación a VRAM
        // ===================================

        mtx_vram.lock();

        std::cout << "[WORKER "
                  << id_worker
                  << "] Asignando Job "
                  << job.id
                  << " a VRAM..."
                  << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(450)
        );

        poolVRAM.push_back(job);

        std::cout << "[WORKER "
                  << id_worker
                  << "] Job "
                  << job.id
                  << " ASIGNADO_VRAM"
                  << std::endl;

        mtx_vram.unlock();

        // ===================================
        // Procesamiento
        // ===================================

        std::cout << "[WORKER "
                  << id_worker
                  << "] Procesando Job "
                  << job.id
                  << "..."
                  << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(600)
        );

        // ===================================
        // Liberación de VRAM
        // ===================================

        mtx_vram.lock();

        std::cout << "[WORKER "
                  << id_worker
                  << "] Liberando Job "
                  << job.id
                  << "..."
                  << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(250)
        );

        for (int i = 0; i < poolVRAM.size(); i++) {

            if (poolVRAM[i].id == job.id) {

                poolVRAM.erase(
                    poolVRAM.begin() + i
                );

                break;
            }
        }

        std::cout << "[WORKER "
                  << id_worker
                  << "] Job "
                  << job.id
                  << " FINALIZADO"
                  << std::endl;

        mtx_vram.unlock();

        // ===================================
        // Libera slot
        // ===================================

        signal(slots_vram);
    }
}