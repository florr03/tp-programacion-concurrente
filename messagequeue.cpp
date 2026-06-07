#include "messagequeue.h"
#include "logger.h"

static const int UMBRAL_AGING_SEGUNDOS = 5;

void push(MessageQueue& mq, Job j) {
    j.estado = EN_COLA;

    {
        std::unique_lock<std::mutex> lock(mq.mtx);

        Entrada e;
        e.job = j;
        e.tiempoEncolado = std::time(nullptr); // Guarda el tiempo en segundos

        if (j.prioridad == 1) {
            mq.colaPremium.push(e);
        } else {
            mq.colaFree.push(e);
        }

        mq.cv.notify_one(); // Avisa a un Worker que esta en espera
    }

    escribirLog(j.id, j.prioridad, "EN_COLA");
}

Job extraer(MessageQueue& mq) {
    std::unique_lock<std::mutex> lock(mq.mtx);

    // Espera pasiva contra Livelock
    while (mq.colaPremium.empty() && mq.colaFree.empty()) {
        mq.cv.wait(lock);
    }

    // --- ALGORITMO DE AGING (Anti-Starvation) ---
    if (!mq.colaFree.empty()) {
        std::time_t ahora = std::time(nullptr);
        double tiempoEspera = std::difftime(ahora, mq.colaFree.front().tiempoEncolado);

        if (tiempoEspera >= UMBRAL_AGING_SEGUNDOS) {
            Job j = mq.colaFree.front().job;
            mq.colaFree.pop();
            return j; // Atiende al Free viejo por equidad
        }
    }

    // Planificacion normal: Primero Premium
    if (!mq.colaPremium.empty()) {
        Job j = mq.colaPremium.front().job;
        mq.colaPremium.pop();
        return j;
    }

    // Si no hay Premium, atiende Free comun
    Job j = mq.colaFree.front().job;
    mq.colaFree.pop();
    return j;
}
