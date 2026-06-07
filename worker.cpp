#include "worker.h"
#include "vram_pool.h"
#include "semaforo.h"
#include "messagequeue.h"
#include "logger.h"
#include "contador.h"
#include <iostream>
#include <thread>

extern const int jobs;
extern std::mutex mtx_cout;
extern MessageQueue messageQueue;

void worker(int id_worker) {
    for (int i = 0; i < jobs / 3; i++) {
        // Extrae del Buffer 1 pasandole la cola global por parametro
        Job job = extraer(messageQueue);

        // ESPERA UN HUECO LIBRE EN VRAM (Semaforo de capacidad)
        wait(slots_vram);

        // SECCION CRITICA 1: Meter a la cola VRAM protegida con Mutex
        mtx_vram.lock();
        poolVRAM.push(job);
        job.estado = ASIGNADO_VRAM;
        escribirLog(job.id, job.prioridad, "ASIGNADO_VRAM");
        mtx_vram.unlock();

        mtx_cout.lock();
        std::cout << "[WORKER " << id_worker << "] Job " << job.id << " ASIGNADO A VRAM." << std::endl;
        mtx_cout.unlock();

        // PROCESAMIENTO PARALELO (Fuera de la exclusion mutua para rendimiento real)
        std::this_thread::sleep_for(std::chrono::milliseconds(600));

        // SECCION CRITICA 2: Sacar de la cola VRAM con Mutex usando .pop() directo
        mtx_vram.lock();
        poolVRAM.pop(); // Saca el que terminó sin usar bucles for
        job.estado = FINALIZADO;
        escribirLog(job.id, job.prioridad, "FINALIZADO");
        incrementarFinalizados();
        mtx_vram.unlock();

        mtx_cout.lock();
        std::cout << "[WORKER " << id_worker << "] Job " << job.id << " FINALIZADO." << std::endl;
        mtx_cout.unlock();

        // SEÑAL: Libera el slot e incrementa el contador del semaforo
        signal(slots_vram);
    }
}
