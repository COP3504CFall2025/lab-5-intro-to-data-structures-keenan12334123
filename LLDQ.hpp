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
        list = LinkedList<T>();
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
            throw std::out_of_range("LLS::pop");
        }
        T temp = ((this->list).getHead())->data;
        (this->list.removeHead());
        return temp;
    }
    T popBack() override {
        if (getSize() == 0) {
            throw std::out_of_range("LLS::pop");
        }
        T temp = ((this->list).getTail())->data;
        (this->list.removeTail());
        return temp;
    }

    // Element Accessors
    const T& front() const override {
        if (getSize() == 0) {
            throw std::runtime_error("Empty stack");
        }
        return ((this->list).getHead())->data;
    }

    const T& back() const override {
        if (getSize() == 0) {
            throw std::runtime_error("Empty stack");
        }
        return ((this->list).getTail())->data;
    }

    void PrintForward() {
        list.printForward();
    }
    void PrintReverse() {
        list.printReverse();
    }
    // Getter
    std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
};






