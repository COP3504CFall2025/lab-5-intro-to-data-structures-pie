#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {
        list = {};
    }

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.AddHead(item);
    }
    void pushBack(const T& item) override {
        list.AddTail(item);
    }
    // Core Removal Operations
    T popFront() override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to pop from front");
        }
        T headData = list.getHead()->data;
        list.RemoveHead();
        return headData;
    }

    T popBack() override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to pop from front");
        }
        T tailData = list.getTail()->data;
        list.RemoveTail();
        return tailData;
    }

    // Element Accessors
    const T& front() const override {
        return list.getHead();
    }
    const T& back() const override {
        return list.getTail();
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






