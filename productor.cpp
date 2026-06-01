#include "productor.h"
#include "messagequeue.h"

#include <iostream>
#include <queue>
#include <mutex>
#include <cstdlib>
#include <chrono>
#include <thread>

// Recursos compartidos
extern std::queue<Job> buffer;

extern MessageQueue hay_espacio;
extern MessageQueue hay_datos;

std::mutex mtx_buffer;

const int tam = 10; // lo puse en 10 para ir probando

int contador = 0; //contador que usa job para el id

// carga el job con 1 free / 2 vip
void cargarJob(Job& j) {

    j.id = contador;
    contador++;

    j.prioridad = (std::rand() % 2) + 1;
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
        mtx_buffer.lock();

        cargarJob(job);
        buffer.push(job); //en el bufer se guarda lo que se cargue en job

        producidos++;


        //esta parte la use para ver que cargaba el cargarJob
        std::cout
            <<"ID: "
            << job.id
            << " prioridad: "
            << job.prioridad
            << std::endl;

        mtx_buffer.unlock();

        // avisa dato disponible
        signal(hay_datos);
    }

        std::cout<<"\n"<<std::endl;
    std::cout << "Producidos: " << producidos << std::endl;
}
