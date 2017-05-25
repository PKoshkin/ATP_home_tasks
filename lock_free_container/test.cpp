#include "lock_free_stack.h"
#include <vector>
#include <thread>

const int THREADS_NUM = 4;
const int SIZE = 1000000;

void testPush(LockFreeStack<int>& stack, int shift) {
    for (int i = shift; i < shift + SIZE; ++i) {
        try {
            stack.push(i);
        //} catch (LockFreeStack::LockFreeStackExeption expection) {
        } catch (LockFreeStackExeption expection) {
            std::cout << "An error while push() occured!" << std::endl;
            exit(1);
        }
    }
}

void testPop(LockFreeStack<int>& stack) {
    for (int i = 0; i < SIZE; ++i) {
        try {
            stack.pop();
        } catch (LockFreeStackExeption expection) {
            std::cout << "An error while pop() occured!" << std::endl;
            exit(1);
        }
    }
}

int main() {
    std::vector<std::thread> threads;
    LockFreeStack<int> stack;
    for (int i = 0; i < THREADS_NUM; ++i) {
        threads.emplace_back(testPush, std::ref(stack), SIZE*i);
    }
    for (int i = 0; i < THREADS_NUM; ++i) {
        threads.emplace_back(testPop, std::ref(stack));
    }
    for (int i = 0; i < THREADS_NUM; ++i) {
        threads[i].join();
    }
    std::cout << "Tests passed" << std::endl;
    return 0;
}
