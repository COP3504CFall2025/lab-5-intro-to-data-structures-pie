#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {
        list = {};
    }

    ~LLS() override = default;

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to pop");
        }

        T headData = list.getHead()->data;
        list.removeHead();
        return headData;
    }

    // Access
    T peek() const override {
        if (getSize() == 0) {
            throw std::runtime_error("nothing to peek");
        }

        return list.getHead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};