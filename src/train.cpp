#include "..\include\train.h"

#include <iostream>
#include <chrono>
#include <random>

#include "functions.h"

bool Train::isPlatformOccupied = false;
using Sec = std::chrono::seconds;

Train::Train(std::string name, int64_t travelTime)
    : m_name(name), m_travelTime(travelTime), m_mtx(std::make_unique<std::mutex>())
{

}

//-----------------------------------------------------------------------------------------

void Train::startMoving() {
    std::this_thread::sleep_for(Sec(m_travelTime));
    std::cout << m_name << " arrived at the station\n";

    std::unique_lock<std::mutex> lock(*m_mtx);

    if (!isPlatformOccupied)
    {
        takePlatform(lock);
    }
    else
    {
        waitForFreePlatform(lock);
        takePlatform(lock);
    }

    sendCommand();

    leavePlatform(lock);
    
}

//-----------------------------------------------------------------------------------------

void Train::takePlatform(std::unique_lock<std::mutex>& lock)
{
    isPlatformOccupied = true;
    std::cout << m_name << " took the platform\n";
    lock.unlock();
}

//-----------------------------------------------------------------------------------------

void Train::waitForFreePlatform(std::unique_lock<std::mutex>& lock)
{
    std::cout << m_name << " is waiting for a free platform\n";
    cv.wait(lock, [this]() { return !isPlatformOccupied; });
}

//-----------------------------------------------------------------------------------------

void Train::leavePlatform(std::unique_lock<std::mutex>& lock)
{
    isPlatformOccupied = false;
    std::cout << m_name << " leave  the station\n";
    cv.notify_all();
}

//-----------------------------------------------------------------------------------------

void Train::sendCommand() const
{
    std::string command = "";
    while (command != "depart")
    {
        std::cout << "Enter \"depart\" to send " << m_name << " from the station\n";
        command = myCin<std::string>();
    }
}