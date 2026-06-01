#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <mutex>
#include <condition_variable>

struct MessageQueue {
    int contador;
    std::mutex mtx;
    std::condition_variable cv;
};

void init(MessageQueue& s, int n);
void wait(MessageQueue& s);
void signal(MessageQueue& s);

#endif
