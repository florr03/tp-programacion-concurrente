#ifndef LOGGER_H
#define LOGGER_H

#include <string>

void escribirLog(
    int id,
    int prioridad,
    const std::string& evento
);

#endif

