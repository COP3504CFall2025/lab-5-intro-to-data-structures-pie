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

    // Insertion
    void enqueue(const T& item) override {
        list.AddTail(item);
    }

    // Deletion
    T dequeue() override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to dequeue");
        }
        T tailData = list.tail()->data;
        list.RemoveTail();
        return tailData;

    }

    // Access
    T peek() const override {
        return list.getTail();
    }
    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};