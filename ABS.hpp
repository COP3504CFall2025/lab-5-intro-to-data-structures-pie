#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}
    ABS(const ABS& other) {
        array_ = new T[other.capacity_];
        for (int i = 0; i < other.capacity_; i++) {
            array_[i] = other.array_[i];
        }
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
    }
    ABS& operator=(const ABS& rhs) {
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
    ABS(ABS&& other) noexcept {
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.array_ = nullptr;
    }
    ABS& operator=(ABS&& rhs) noexcept {
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

    ~ABS() noexcept override {
        delete [] array_;
        array_ = nullptr;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ < capacity_) {
            array_[curr_size_] = data;
            curr_size_++;
        }
        else {
            resize(capacity_*2);
            array_[curr_size_] = data;
            curr_size_++;
        }
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("empty stack");
        }
        return array_[curr_size_-1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("empty stack");
        }

        T temp = array_[curr_size_-1];
        curr_size_--;

        if (getMaxCapacity() == 1) {
            return temp;
        }
        if (getMaxCapacity() == 2 && getSize() <= getMaxCapacity()/2) {
            resize(getMaxCapacity()/2);
        }
        else if (getSize() <= getMaxCapacity()/4) {
            resize(getMaxCapacity()/2);
        }
        return temp;
    }


private:
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
};
