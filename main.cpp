#include "productor.h"
#include "messagequeue.h"

#include <iostream>
#include <thread>
#include <queue>

std::queue<Job> buffer;

// Semaforo bufer message queue
MessageQueue hay_espacio;
MessageQueue hay_datos;

int main()
{
    init(hay_espacio, 10);

    init(hay_datos, 0);

    std::thread t1(productor);

    t1.join();

    //esta parte lo hice para verificar que se guardaba en el bufer los datos
        std::queue<Job> copia = buffer;
        std::cout<<"\n"<<std::endl;
        while (!copia.empty()) {
            Job j = copia.front();
            std::cout << "ID: " << j.id
                      << " Prioridad: " << j.prioridad
                      << std::endl;

            copia.pop();
        }

    return 0;
}
