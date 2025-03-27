#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <vector>
#include <concepts>
#include <stdexcept>
#include <cstddef>
#include <numeric>
#include <concepts>
#include <iostream>

template <typename T>
concept Arithmetic = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a / 1 } -> std::convertible_to<T>;
};

template <Arithmetic T>
class CircularBuffer {
public:
    explicit CircularBuffer(size_t capacity);

    void push(T value);
    T pop();
    size_t getSize() const;
    size_t getCapacity() const;
    double getAverage() const;
    void printBuffer();


private:
    std::vector<T> buffer;
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
    size_t capacity;
};

template <Arithmetic T>
CircularBuffer<T>::CircularBuffer(size_t capacity)
    : buffer(capacity), capacity(capacity) {}

template <Arithmetic T>
void CircularBuffer<T>::push(T value) {
    buffer[tail] = value;
    tail = (tail + 1) % capacity;

    if (count < capacity) {
        ++count;
    } else {
        head = (head + 1) % capacity;
    }
}

template <Arithmetic T>
T CircularBuffer<T>::pop() {
    if (count == 0) throw std::runtime_error("Buffer is empty");
    tail = (tail + capacity - 1) % capacity;
    T value = buffer[tail];
    --count;
    return value;
}

template <Arithmetic T>
size_t CircularBuffer<T>::getSize() const {
    return count;
}

template <Arithmetic T>
size_t CircularBuffer<T>::getCapacity() const {
    return capacity;
}

template <Arithmetic T> 
double CircularBuffer<T>::getAverage() const{
    if (count < 5) return 0.0;
    double sum = 0.0;
    for (size_t i = 0, idx = head; i < count; ++i, idx = (idx + 1) % capacity) {
        sum += buffer[idx];
    }
    return sum / count;
}

template <Arithmetic T>
void CircularBuffer<T>::printBuffer(){
    for (size_t i = 0; i < count; ++i) {
        std::cout << buffer[(head + i) % capacity] << " ";
    }
    std::cout << std::endl;
}

#endif // CIRCULAR_BUFFER_HPP
