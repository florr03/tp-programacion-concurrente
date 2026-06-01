#include "productor.h"
#include "semaforo.h"

#include <iostream>
#include <queue>
#include <mutex>
#include <cstdlib>
#include <chrono>
#include <thread>

// Recursos compartidos
extern std::queue<Job> messageQueue;

extern Semaforo hay_espacio;
extern Semaforo hay_datos;

extern std::mutex mtx_queue;

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

        // espera espacio
        wait(hay_espacio);
        //duerme por 100 ms antes de iniciar
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // mutex cola
        mtx_queue.lock();

        cargarJob(job);
        messageQueue.push(job); //en el bufer se guarda lo que se cargue en job

        producidos++;


        //esta parte la use para ver que cargaba el cargarJob
        std::cout
            <<"ID: "
            << job.id
            << " prioridad: "
            << job.prioridad
            << std::endl;

        mtx_queue.unlock();

        // avisa dato disponible
        signal(hay_datos);
    }

        std::cout<<"\n"<<std::endl;
    std::cout << "Producidos: " << producidos << std::endl;
}
