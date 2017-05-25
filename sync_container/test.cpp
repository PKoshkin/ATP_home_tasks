#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>

#include "sync_container.h"

int main() {
    int vectorInts[10], listInts[10], queueInts[10], dequeInts[10], stackInts[10];

    SyncContainer< std::vector<int> > vector;
    SyncContainer< std::list<int> > list;
    SyncContainer< std::deque<int> > deque;
    SyncContainer< std::queue<int> > queue;
    SyncContainer< std::stack<int> > stack;
    for (int i = 0; i < 10; ++i) {
        vector.push(i);
        list.push(i);
        deque.push(i);
        queue.push(i);
        stack.push(i);
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << vector.popOrSleep();
        std::cout << " " << list.popOrSleep();
        std::cout << " " << deque.popOrSleep();
        std::cout << " " << queue.popOrSleep();
        std::cout << " " << stack.popOrSleep();
        std::cout << std::endl;
    }

    std::cout << "done" << std::endl;
    
    return 0;
}
