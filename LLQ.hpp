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
        list = LinkedList<T>();
    }

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (getSize() == 0) {
            throw std::out_of_range("LLS::pop");
        }
        T temp = ((this->list).getTail())->data;
        (this->list.removeTail());
        return temp;
    }

    // Access
    T peek() const override {
        if (getSize() == 0) {
            throw std::runtime_error("Empty stack");
        }
        return ((this->list).getTail())->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
    void PrintForward() {
        list.printForward();
    }
    void PrintReverse() {
        list.printReverse();
    }

};