#include "contador.h"
#include <mutex>

int tareasFinalizadas = 0;
std::mutex mtx_contador;

void incrementarFinalizados() {
    mtx_contador.lock();
    tareasFinalizadas++;
    mtx_contador.unlock();
}

int obtenerFinalizados() {
    mtx_contador.lock();
    int valor = tareasFinalizadas;
    mtx_contador.unlock();
    return valor;
}
