#include "worker.h"
#include "vram_pool.h"
#include "semaforo.h"

#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>

// Cola compartida
extern std::queue<Job> messageQueue;

// Semáforo de jobs disponibles
extern Semaforo hay_datos;

// Mutex de la cola
extern std::mutex mtx_queue;

void worker(int id_worker) {

    while (true) {

        // ===================================
        // Espera jobs disponibles
        // ===================================

        wait(hay_datos);

        // ===================================
        // Extrae job de la cola
        // ===================================

        mtx_queue.lock();

        if (messageQueue.empty()) {

            mtx_queue.unlock();

            continue;
        }

        Job job = messageQueue.front();

        messageQueue.pop();

        mtx_queue.unlock();

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