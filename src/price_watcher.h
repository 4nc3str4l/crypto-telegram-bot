#pragma once

#include <thread>

class PriceWatcher
{
public:
    static PriceWatcher &shared_instance() {static PriceWatcher watcher; return watcher;}
    ~PriceWatcher();
    void start();
    void stop();
private:
    PriceWatcher(){};
    void checkLoop();
private:
    bool m_running;
    int m_checkInterval = 60;
    std::thread t;
};