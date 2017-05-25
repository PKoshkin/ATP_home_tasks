#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <functional>    

const int NUMBER_OF_THREADS = 4;
const int SECONDS = 5;

auto getHash = std::hash<std::thread::id>();

std::size_t NULL_THREAD = getHash(std::thread::id());

class Futex {
private:
    std::atomic<std::size_t> id;

public:
    Futex();
    void lock();
    void unlock();
};

Futex::Futex() {
    id.store(NULL_THREAD);
}

void Futex::lock() {
    std::size_t save = NULL_THREAD;
    while (!id.compare_exchange_strong(save, getHash(std::this_thread::get_id()))) {
        save = NULL_THREAD;
    }
}

void Futex::unlock() {
    id.store(NULL_THREAD);
}

int number = 0;
Futex futex;
std::chrono::steady_clock::time_point beginTime;

void work(std::size_t* iterations) {
    using namespace std::chrono;
    while(true) {
        duration<double> currentTime = duration_cast< duration<double> >(steady_clock::now() - beginTime);
        if (currentTime.count() < SECONDS) {
            futex.lock();

            std::cout << "working" << std::endl;


            ++number;
            ++(*iterations);
            futex.unlock();
        } else {
            break;
        }
    }
}

int main() {
    std::vector<std::thread> threads;
    std::vector<std::size_t> threadsIterations;
    beginTime = std::chrono::steady_clock::now();
    for (std::size_t i = 0; i < NUMBER_OF_THREADS; ++i) {
        threadsIterations.push_back(0);
        threads.push_back(std::thread(work, &threadsIterations[i]));
    }

    for (std::size_t i = 0; i < NUMBER_OF_THREADS; ++i) {
        threads[i].join();
    }
    
    std::cout << "number: " << number << std::endl;
    std::size_t sum = 0;
    for (std::size_t i = 0; i < NUMBER_OF_THREADS; ++i) {
        std::cout << threadsIterations[i] << " ";
        sum += threadsIterations[i];
    }
    std::cout << std::endl << "sum: " << sum << std::endl; 
    return 0;
}
