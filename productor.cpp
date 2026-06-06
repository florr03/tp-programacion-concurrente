#include "productor.h"
#include "messagequeue.h"
#include "logger.h"

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

// Recurso compartido
extern MessageQueue messageQueue;

std::mutex mtx_contador_id;
std::mutex mtx_cout;

const int tam = 10; // lo puse en 10 para ir probando

int contador = 0; //contador que usa job para el id

// carga el job con 0 free / 1 premium
void cargarJob(Job& j) {
    //aguegue mutex por si se pisan los productores
    mtx_contador_id.lock();
    j.id = contador;
    contador++;
    mtx_contador_id.unlock();

    j.prioridad = std::rand() % 2;
}

// el tamanio varia segun la cantidad de productores, ejemplo: 2 productores seria tam/2
void productor(int id_productor) {

    int producidos = 0;

    Job job;

    for (int i = 0; i < tam/2; i++) {

        //duerme por 100 ms antes de iniciar
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        cargarJob(job);
        escribirLog(
        job.id,
        job.prioridad,
        "CREADO"
        );

        messageQueue.push(job);

        mtx_cout.lock();

        std::cout
            << "[PRODUCTOR "
            << id_productor
            << "] Job "
            << job.id
            << " prioridad "
            << job.prioridad
            << std::endl;

        mtx_cout.unlock();

        producidos++;

        //esta parte la use para ver que cargaba el cargarJob
    }
    mtx_cout.lock();
    std::cout << "Producidos: " << producidos << std::endl;
    mtx_cout.unlock();
}
