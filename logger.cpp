#include "logger.h"

#include <fstream>
#include <mutex>
#include <chrono>
#include <ctime>

std::mutex mtx_log;

void escribirLog(
    int id,
    int prioridad,
    const std::string& evento
)
{
    mtx_log.lock();

    std::ofstream archivo(
        "sistema.log",
        std::ios::app
    );

    std::time_t ahora =
        std::time(nullptr);

    std::string fecha = std::ctime(&ahora);

    fecha.pop_back();


    archivo
    << "[" << fecha << "] - Job "
    << id
    << " - Prioridad "
    << prioridad
    << " - "
    << evento
    << std::endl;

    archivo.close();

    mtx_log.unlock();
}

