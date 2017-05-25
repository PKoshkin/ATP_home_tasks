#ifndef LOCK_FREE_STACK_KOSHKIN_493
#define LOCK_FREE_STACK_KOSHKIN_493

#include <atomic>
#include <iostream>

template <class T>
struct Node {
    Node* next;
    T data;

    Node(T element) : data(element) {}
};
    
class LockFreeStackExeption {
public:
    LockFreeStackExeption() {}
};

template<class T>
class LockFreeStack {
private:
    std::atomic< Node<T>* > head;
public:
    LockFreeStack() : head(nullptr) {}
    void push(T element);
    T pop();
};

template <class T>
void LockFreeStack<T>::push(T element) {
    Node<T>* newNode = new Node<T>(element);
    while (!head.compare_exchange_strong(newNode->next, newNode)) {}
}

template <class T>
T LockFreeStack<T>::pop() {
    Node<T>* temp = head;
    if (temp == nullptr) {
        throw LockFreeStackExeption();
    }
    while(!head.compare_exchange_strong(temp, temp->next)) {
        if (temp == nullptr) {
            throw LockFreeStackExeption();
        }
    }
    T value = temp->data;
    delete temp;
    return value;
}

#endif
