#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {
        list = {};
    }

    ~LLQ() override = default;

    LLQ(const LLQ<T>& other) {
        list = other.list;
    }

    LLQ(LLQ<T>&& other) noexcept {
        list = std::move(other.list);
    }

    LLQ& operator=(const LLQ& other) {
        if (this == &other) return *this;
        list = other.list;
        return *this;
    }

    LLQ& operator=(LLQ&& other) noexcept {
        if (this == &other) return *this;
        list = std::move(other.list);
        return *this;
    }

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to dequeue");
        }
        T headData = list.getHead()->data;
        list.removeHead();
        return headData;

    }

    // Access
    T peek() const override {
        return list.getTail()->data;
    }
    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};