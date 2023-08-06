#pragma once

#include <iostream>
#include <string>
#include <mutex>
#include <memory>

static std::condition_variable cv;

class Train {
public:
    Train(std::string name, int64_t travelTime);

    void startMoving();

private:
    std::string m_name;
    int m_travelTime;
};

