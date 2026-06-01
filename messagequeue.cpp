#include "messagequeue.h"
#include <mutex>
#include <condition_variable>


void init(MessageQueue& s, int n) {
    s.contador = n;
}

void wait(MessageQueue& s) {
    std::unique_lock<std::mutex> lock(s.mtx);

    while (s.contador == 0) {
        s.cv.wait(lock);
    }

    s.contador--;
}

void signal(MessageQueue& s) {
    std::unique_lock<std::mutex> lock(s.mtx);

    s.contador++;
    s.cv.notify_one();
}
