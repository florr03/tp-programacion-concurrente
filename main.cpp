#include <iostream>
#include <thread>
#include "productor.h"
#include "worker.h"
#include "vram_pool.h"
#include "messagequeue.h"

// Variables compartidas globales
MessageQueue messageQueue;
std::mutex mtx_cout;
extern const int jobs = 15;

int main() {
    std::cout << "=== Iniciando Granja de Renderizado Concurrente ===" << std::endl;
    initVRAM(); // Inicializa el semaforo

    // Lanzamiento de los hilos
    std::thread t_prod1(productor, 1);
    std::thread t_prod2(productor, 2);
    std::thread t_prod3(productor, 3);

    std::thread w1(worker, 1);
    std::thread w2(worker, 2);
    std::thread w3(worker, 3);

    // Sincronizacion final (.join())
    t_prod1.join();
    t_prod2.join();
    t_prod3.join();

    w1.join();
    w2.join();
    w3.join();

    std::cout << "=== Simulacion Finalizada Correctamente ===" << std::endl;
    return 0;
}
