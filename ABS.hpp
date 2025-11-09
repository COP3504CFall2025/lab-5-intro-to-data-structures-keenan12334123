#pragma once
#include<iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        this->capacity_ = 1;
        this->curr_size_ = 0;
        this->array_ = new T[capacity_];
    }
    explicit ABS(const size_t capacity) {
        this->capacity_ = capacity;
        this->curr_size_ = 0;
        this->array_ = new T[capacity_];
    }

    ABS(const ABS& other) : array_(new T[other.capacity_]), capacity_(other.capacity_), curr_size_(other.curr_size_) {
        for (int i = 0; i < other.curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) return *this;
        T* new_arr = new T[rhs.capacity_];
        delete[] this->array_;

        this->array_ = new_arr;
        this->capacity_ = (rhs.capacity_);
        this->curr_size_ = (rhs.curr_size_);
        for (int i = 0; i < rhs.curr_size_; i++) {
            array_[i] = rhs.array_[i];
        }
        return *this;
    }

    ABS(ABS&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 1;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delete[] this->array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->array_ = rhs.array_;

        rhs.array_ =nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 1;
        return *this;
    }
    ~ABS() noexcept override {
        delete[] this->array_;
        this->array_ = nullptr;
        this->curr_size_ = 0;
        this->capacity_ = 1;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return this->curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return this->capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return this->array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (this->curr_size_ == this->capacity_) {
            T newCapacity = this->capacity_ * 2;
            this->capacity_ = newCapacity;
        }
        T* tempArray = new T[this->capacity_ * 2];
        tempArray[0] = data;
            for (size_t i = 0; i < this->curr_size_; ++i) {
                tempArray[i + 1] = this->array_[i];
            }
        delete[] this->array_;
        this->array_ = tempArray;
        this->curr_size_ += 1;
    }

    T peek() const override {
        if (this->curr_size_ == 0) {
            throw std::runtime_error("Empty stack");
        }
        return this->array_[this->curr_size_ - 1];
    }

    T pop() override {
        if (this->curr_size_ == 0) {
            throw std::runtime_error("Empty stack");
        }
        else {
            T* temp = new T[this->capacity_];
            T test = this->array_[this->curr_size_ - 1];
            for (size_t i = 0; i < this->curr_size_ - 1; ++i) {
                temp[i] = this->array_[i];
            }
            delete[] this->array_;
            this->array_ = temp;
            this->curr_size_ -= 1;

            if (this->curr_size_ * 2 < this->capacity_ && this-> capacity_ > 1) {
                this->capacity_ /= 2;
            }
            return test;
        }
    }
    void PrintForward() {
        for (int i = 0; i < this->curr_size_; i++) {
            std::cout << this->array_[i] << std::endl;
        }
    }
    void PrintReverse() {
        for (int i = curr_size_; i < 0; --i) {
            std::cout << this->array_[i] << std::endl;
        }
    }
};
