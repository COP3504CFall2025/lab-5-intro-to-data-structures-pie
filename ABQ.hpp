#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T> {
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

    void resize(std::size_t newCap) {
        T* newArray = new T[newCap];
        for (int i = 0; i < capacity_; i++) {
            newArray[i] = array_[i];
        }
        delete [] array_;
        array_ = newArray;
        capacity_ = newCap;
    }

public:
    // Constructors + Big 5
    ABQ() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}
    ABQ(const ABQ& other) {
        array_ = new T[other.capacity_];
        for (int i = 0; i < other.capacity_; i++) {
            array_[i] = other.array_[i];
        }
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;

    }
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) return *this;
        delete [] array_;
        array_ = new T[rhs.capacity_];
        for (int i = 0; i < rhs.capacity_; i++) {
            array_[i] = rhs.array_[i];
        }
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        return *this;

    }
    ABQ(ABQ&& other) noexcept {
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) return *this;
        delete [] array_;
        array_ = rhs.array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        rhs.array_ = nullptr;
        return *this;
    }

    ~ABQ() noexcept override {
        delete [] array_;
        array_ = nullptr;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (getSize() < getMaxCapacity()) {
            array_[curr_size_] = data;
            curr_size_++;
        }
        else {
            resize(curr_size_ * 2);
            array_[curr_size_] = data;
            curr_size_++;
        }
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) throw std::runtime_error("empty queue");
        return array_[0];
    }

    // Deletion
    T dequeue() override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to dequeue");
        }

        T result = array_[0];
        for (int i = 0; i < curr_size_-1; i++) {
            array_[i] = array_[i+1];
        }

        curr_size_--;
        if (getMaxCapacity() == 1) {
            return result;
        }
        if (getMaxCapacity() == 2 && getSize() <= getMaxCapacity()/2) {
            resize(getMaxCapacity()/2);
        }
        else if (getSize() <= getMaxCapacity()/4) {
            resize(getMaxCapacity()/2);
        }
        return result;
    }

};
