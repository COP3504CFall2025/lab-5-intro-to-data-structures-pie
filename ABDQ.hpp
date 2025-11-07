#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : data_(new T[1]), capacity_(1), size_(0),front_(0), back_(0) {}
    explicit ABDQ(std::size_t capacity) : data_(new T[1]), capacity_(capacity), size_(0), front_(0), back_(0) {}
    ABDQ(const ABDQ& other) {
        data_ = new T[other.capacity_];
        for (int i = 0; i < other.capacity_; i++) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
    }
    ABDQ(ABDQ&& other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;
        delete [] data_;
        data_ = new T[other.capacity_];
        for(int i = 0; i < other.capacity_; i++) {
            data_[i] = other.data_[i];
        }

        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;
        delete [] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    ~ABDQ() override {
        delete [] data_;
        data_ = nullptr;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == 0) {
            front_ = 0;
            back_ = 1;
            data_[0] = item;
            size_++;
        }
        else {
            ensureCapacity();
            front_ = (front_ - 1)%capacity_;
            data_[front_] = item;
            size_++;
        }
    }

    void pushBack(const T& item) override {
        if (size_ == 0) {
            front_ = 0;
            back_ = 1;
            data_[0] = item;
            size_++;
        }
        else {
            ensureCapacity();
            back_ = (back_+1)%capacity_;
            data_[(back_-1)%capacity_] = item;
            size_++;
        }
    }

    // Deletion
    T popFront() override {
        if (getSize() == 0) {
            throw std::runtime_error("empty deque");
        }
        T frontData = data_[front_];
        front_ = (front_+1)%capacity_;
        size_--;
        shrinkIfNeeded();
        return frontData;
    }
    T popBack() override {
        if (getSize() == 0) {
            throw std::runtime_error("empty deque");
        }
        T backData = data_[(back_-1)%capacity_];
        back_ = (back_ - 1)%capacity_;
        size_--;
        shrinkIfNeeded();
        return backData;
    }

    // Access
    const T& front() const override {
        if (getSize() == 0) {
            throw std::runtime_error("empty deque");
        }
        return data_[front_%capacity_];
    }
    const T& back() const override {
        if (getSize() == 0) {
            throw std::runtime_error("empty deque");
        }
        return data_[back_%capacity_ - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    std::size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    void resize(std::size_t newCap) {
        T* newData = new T[newCap];
        for (int i = 0; i < size_; i++) {
            newData[i] = data_[(front_+i)%capacity_];
        }

        front_ = 0;
        back_ = size_%newCap;
        delete [] data_;
        data_ = newData;
        capacity_ = newCap;
    }

    void ensureCapacity() {
        if (getSize() >= getMaxCapacity()) {
            resize(capacity_*2);
        }
    }

    void shrinkIfNeeded() {
        if (getMaxCapacity() == 1) {
            return;
        }

        if ((getMaxCapacity() == 2 && getSize() <= getMaxCapacity()/2) || getSize() <= getMaxCapacity()/4) {
            resize(getMaxCapacity()/2);
        }
    }
};
