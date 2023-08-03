#pragma once

#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <future>
#include <memory>

static std::condition_variable cv;

class Train {
public:
    Train(std::string name, int64_t travelTime);

    void startMoving();

private:
    std::string m_name;
    int m_travelTime;
    std::unique_ptr<std::mutex> m_mtx;
    static bool isPlatformOccupied;

    void takePlatform(std::unique_lock<std::mutex>& lock);
    void waitForFreePlatform(std::unique_lock<std::mutex>& lock);
    void leavePlatform(std::unique_lock<std::mutex>& lock);
    void sendCommand() const;
};

