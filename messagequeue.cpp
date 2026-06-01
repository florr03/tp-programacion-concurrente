#include "messagequeue.h"
#include "logger.h"

// Umbral de aging: un Job Free que espero al menos este tiempo
// se despacha por encima de los Premium (anti-starvation).
static const int UMBRAL_ANTI_STARVATION_MS = 5000;

void MessageQueue::push(Job j) {
    j.estado = EN_COLA;

    {
        std::unique_lock<std::mutex> lock(mtx);

        Entrada e;
        e.job = j;
        e.tiempoEncolado = std::chrono::high_resolution_clock::now();

        if (j.prioridad == 1) {
            colaPremium.push(e);
        } else {
            colaFree.push(e);
        }

        cv.notify_one();
    }

    escribirLog(j.id, j.prioridad, "EN_COLA");
}

Job MessageQueue::extraer() {
    std::unique_lock<std::mutex> lock(mtx);

    // Espera pasiva si no hay nada
    while (colaPremium.empty() && colaFree.empty()) {
        cv.wait(lock);
    }

    // Politica de despacho (Scheduler):
    // 1. Si el Free al frente ya espero >= 5000ms, lo despachamos (aging)
    // 2. Si hay Premium, despachamos Premium
    // 3. Sino, despachamos Free
    if (!colaFree.empty()) {
        std::chrono::high_resolution_clock::time_point ahora =
            std::chrono::high_resolution_clock::now();

        long espera = std::chrono::duration_cast<std::chrono::milliseconds>(
            ahora - colaFree.front().tiempoEncolado
        ).count();

        if (espera >= UMBRAL_ANTI_STARVATION_MS) {
            Job j = colaFree.front().job;
            colaFree.pop();
            return j;
        }
    }

    if (!colaPremium.empty()) {
        Job j = colaPremium.front().job;
        colaPremium.pop();
        return j;
    }

    Job j = colaFree.front().job;
    colaFree.pop();
    return j;
}
