#include <iostream>
#include <thread>
#include <limits>
#include <stdlib.h>

const int N = std::numeric_limits<int>::max();

void function(int* array, int index) {
    for (int i = 0; i < N; ++i) {
        ++array[index];
    }
}

int main(int argc, char** argv) {
    int index = atoi(argv[1]);
    int* array = new int[index + 1];
    array[0] = 0;
    array[index] = 0;
    std::thread thread1(function, array, 0);
    std::thread thread2(function, array, index);
    
    thread1.join();
    thread2.join();


    return 0;
}
