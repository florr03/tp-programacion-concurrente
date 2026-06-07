#include "productor.h"
#include "messagequeue.h"
#include "logger.h"
#include <iostream>
#include <cstdlib>
#include <thread>

extern MessageQueue messageQueue;
extern const int jobs;

std::mutex mtx_contador_id;
extern std::mutex mtx_cout;
int contador = 0;

void cargarJob(Job& j) {
    mtx_contador_id.lock(); // Mutex clasico para seccion critica
    j.id = contador;
    contador++;
    mtx_contador_id.unlock();

    j.prioridad = std::rand() % 2; // 0 o 1
}

void productor(int id_productor) {
    Job job;
    for (int i = 0; i < jobs / 3; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        cargarJob(job);
        escribirLog(job.id, job.prioridad, "CREADO");

        // Llama a la funcion push global pasandole la cola como referencia
        push(messageQueue, job);

        mtx_cout.lock();
        std::cout << "[PRODUCTOR " << id_productor << "] Job " << job.id
                  << " ingresado a la cola." << std::endl;
        mtx_cout.unlock();
    }
}
