#ifndef SYNC_CONTAINER_KOSHKIN_493
#define SYNC_CONTAINER_KOSHKIN_493

#include <condition_variable>
#include <mutex>
#include <string>

template<class Array>
class SyncContainer {
private:
    typedef typename Array::value_type Value;

    Array data;
    std::mutex mutex;
    std::condition_variable signal;
public:
    void push(Value element);
    Value popOrSleep();
    Value popNoSleep();

    class SyncContainerExeption {
    private:
        std::string errorMessage;
    public:
        SyncContainerExeption(const std::string& message) : errorMessage(message) {}
    };
};

// Метод _top нужен для _pop
template <class Array>
auto _top(Array& container, int) -> decltype(container.top(), typename Array::value_type()) {
    return container.top();
}

template <class Array>
auto _top(Array& container, long) -> decltype(container.pop(), typename Array::value_type()) {
    return container.front();
}

template <class Array>
auto _top(Array& container, long long) -> decltype(container.pop_back(), typename Array::value_type()) {
    return container.back();
}

// Методы _push и _pop будут компилироваться нужными для нужного контейнера.
// Нужно устроить ошибку в загаловке, если метод не должен компилироваться для какого-то контейнера.
template <class Array>
auto _push(Array& container, typename Array::value_type element, int) -> decltype(container.push(element), void()) {
    container.push(element);
}

template <class Array>
auto _push(Array& container, typename Array::value_type element, long) -> decltype(container.push_back(element), void()) {
    container.push_back(element);
}

template <class Array>
auto _pop(Array& container, int) -> decltype(container.pop(), typename Array::value_type()) {
    typename Array::value_type result = _top(container, 0);
    container.pop();
    return result;
}

template <class Array>
auto _pop(Array& container, long) -> decltype(container.pop_back(), typename Array::value_type()) {
    typename Array::value_type result = _top(container, 0);
    container.pop_back();
    return result;
}

template<class Array>
void SyncContainer<Array>::push(typename Array::value_type element) {
    std::unique_lock<std::mutex> lock(mutex);
    _push(data, element, 0);
    signal.notify_one();
}

template<class Array>
typename SyncContainer<Array>::Value SyncContainer<Array>::popOrSleep() {
    std::unique_lock<std::mutex> lock(mutex);
    while (data.empty()) {
        signal.wait(lock);
    }
    return _pop(data, 0);
}

template<class Array>
typename Array::value_type SyncContainer<Array>::popNoSleep() {
    std::lock_guard<std::mutex> lock(mutex);
    if (data.empty()) {
        throw SyncContainerExeption("Container is empty");
    } else {
        return _pop(data, 0);
    }
}

#endif
