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
    ABDQ() : data_(nullptr), capacity_(1), size_(0),front_(0), back_(0) {}
    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0) {}
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
    }
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() override;

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;

};
