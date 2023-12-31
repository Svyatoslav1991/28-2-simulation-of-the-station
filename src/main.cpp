#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <thread>

#include "train.h"
#include "functions.h"

int main() {
	std::cout << "\tTASK 28.2 SIMULATION OF THE STATION\n\n";

    srand(time(NULL));
    std::vector<Train> vTrains;
    
    Train trainA("train_A", rand() % 6 + 3);
    Train trainB("train_B", rand() % 6 + 3);
    Train trainC("train_C", rand() % 6 + 3);

    vTrains.push_back(std::move(trainA));
    vTrains.push_back(std::move(trainB));
    vTrains.push_back(std::move(trainC));

    std::vector<std::thread> vThreads;
    for (auto& train : vTrains) {
        vThreads.push_back(std::thread(&Train::startMoving, &train));
    }

    for (auto& thread : vThreads) {
        thread.join();
    }


	return 0;
}