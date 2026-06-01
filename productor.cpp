#include "productor.h"
#include "messagequeue.h"

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

// Recurso compartido
extern MessageQueue messageQueue;

const int tam = 10; // lo puse en 10 para ir probando

int contador = 0; //contador que usa job para el id

// carga el job con 0 free / 1 premium
void cargarJob(Job& j) {

    j.id = contador;
    contador++;

    j.prioridad = std::rand() % 2;
}

void productor() {

    int producidos = 0;

    Job job;

    for (int i = 0; i < tam; i++) {

        //duerme por 100 ms antes de iniciar
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        cargarJob(job);
        messageQueue.push(job);

        producidos++;

        //esta parte la use para ver que cargaba el cargarJob
        std::cout
            <<"ID: "
            << job.id
            << " prioridad: "
            << job.prioridad
            << std::endl;
    }

        std::cout<<"\n"<<std::endl;
    std::cout << "Producidos: " << producidos << std::endl;
}
