#include "..\include\train.h"

#include <iostream>
#include <chrono>
#include <random>

#include "functions.h"

using Sec = std::chrono::seconds;

static std::mutex m_mtx1;
static std::mutex m_mtx2;

Train::Train(std::string name, int64_t travelTime)
    : m_name(name), m_travelTime(travelTime)
{

}

//-----------------------------------------------------------------------------------------

void Train::startMoving() {
    std::this_thread::sleep_for(Sec(m_travelTime));


    if (!m_mtx2.try_lock())
    {
        m_mtx1.lock();
        std::cout << m_name << " arrived at the station\n";
        m_mtx1.unlock();
        m_mtx2.lock();
    }


    std::cout << m_name << " is at the station\n";

    std::string command = "";

    do
    {
        std::cout << "Enter depart to let " << m_name << " go\n";
        command = myCin<std::string>();
    } while (command != "depart");

    std::cout << m_name << " leave the station\n";
    m_mtx2.unlock();
}