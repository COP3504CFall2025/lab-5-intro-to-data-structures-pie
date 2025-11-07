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

    ~LLDQ() override = default;

    LLDQ(const LLDQ<T>& other) {
        list = other.list;
    }

    LLDQ(LLDQ<T>&& other) noexcept {
        list = std::move(other.list);
    }

    LLDQ& operator=(const LLDQ& other) {
        if (this == &other) return *this;
        list = other.list;
        return *this;
    }

    LLDQ& operator=(LLDQ&& other) noexcept {
        if (this == &other) return *this;
        list = std::move(other.list);
        return *this;
    }

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }
    // Core Removal Operations
    T popFront() override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to pop from front");
        }
        T headData = list.getHead()->data;
        list.removeHead();
        return headData;
    }

    T popBack() override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to pop from back");
        }
        T tailData = list.getTail()->data;
        list.removeTail();
        return tailData;
    }

    // Element Accessors
    const T& front() const override {
        if (getSize() == 0) {
            throw std::runtime_error("empty queue");
        }
        return list.getHead()->data;
    }
    const T& back() const override {
        if (getSize() == 0) {
            throw std::runtime_error("empty queue");
        }
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};






