#include "worker.h"
#include "vram_pool.h"
#include "semaforo.h"
#include "messagequeue.h"
#include "logger.h"
#include "contador.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

extern const int jobs;
extern std::mutex mtx_cout;

// Cola compartida (Buffer 1)
extern MessageQueue messageQueue;

void worker(int id_worker) {

    for (int i = 0; i < jobs/3; i++)  {

        Job job = messageQueue.extraer();

        wait(slots_vram);

        // Asignación a VRAM

        mtx_vram.lock();

        mtx_cout.lock();
        std::cout << "[WORKER "
                  << id_worker
                  << "] Asignando Job "
                  << job.id
                  << " a VRAM..."
                  << std::endl;
        mtx_cout.unlock();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(450)
        );

        poolVRAM.push_back(job);

        job.estado = ASIGNADO_VRAM;

        escribirLog(
            job.id,
            job.prioridad,
            "ASIGNADO_VRAM"
        );

        mtx_cout.lock();
        std::cout << "[WORKER "
                  << id_worker
                  << "] Job "
                  << job.id
                  << " ASIGNADO_VRAM"
                  << std::endl;
        mtx_cout.unlock();

        mtx_vram.unlock();

        // Procesamiento

        mtx_cout.lock();
        std::cout << "[WORKER "
                  << id_worker
                  << "] Procesando Job "
                  << job.id
                  << "..."
                  << std::endl;
        mtx_cout.unlock();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(600)
        );

        // Liberación de VRAM


        mtx_vram.lock();

        mtx_cout.lock();
        std::cout << "[WORKER "
                  << id_worker
                  << "] Liberando Job "
                  << job.id
                  << "..."
                  << std::endl;
        mtx_cout.unlock();

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

        mtx_cout.lock();
        std::cout << "[WORKER "
                  << id_worker
                  << "] Job "
                  << job.id
                  << " FINALIZADO"
                  << std::endl;
        mtx_cout.unlock();

        job.estado = FINALIZADO;

        escribirLog(
            job.id,
            job.prioridad,
            "FINALIZADO"
        );

        incrementarFinalizados();

        mtx_vram.unlock();

        signal(slots_vram);
    }
}
