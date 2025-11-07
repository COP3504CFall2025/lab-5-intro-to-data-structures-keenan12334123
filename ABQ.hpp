#pragma once
#include<iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

    public:
    // Constructors + Big 5
    ABQ(){
        capacity_ =  1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    explicit ABQ(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    ABQ(const ABQ& other) : array_(new T[other.capacity_]), capacity_(other.capacity_), curr_size_(other.curr_size_) {
        for (size_t i = 0; i < other.curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) return *this;
        T* new_arr = new T[rhs.capacity_];
        delete[] this->array_;

        this->array_ = new_arr;
        this->capacity_ = (rhs.capacity_);
        this->curr_size_ = (rhs.curr_size_);
        for (size_t i = 0; i < rhs.curr_size_; i++) {
            array_[i] = rhs.array_[i];
        }
        return *this;
    }

    ABQ(ABQ&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delete[] this->array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->array_ = rhs.array_;

        rhs.array_ =nullptr;
        rhs.curr_size_ = 0;
        rhs.curr_size_ = 0;
        return *this;
    }
    ~ABQ() noexcept override {
        delete[] this->array_;
        this->array_ = nullptr;
        this->curr_size_ = 0;
        this->capacity_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return this->curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return this->capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return this->array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        T* doubleArray;
        if (this->curr_size_ == this->capacity_) {
            doubleArray = new T(this->capacity_ * 2);
            this->capacity_ *= 2;
        }
        else {
            doubleArray = new T(this->capacity_);
        }
        for (size_t i = 0; i < this->curr_size_; i++) {
            doubleArray[i] = array_[i];
        }
        doubleArray[this->curr_size_] = data;
        delete[] this->array_;
        array_ = doubleArray;
        doubleArray = nullptr;
        this->curr_size_ += 1;
    }

    // Access
    T peek() const override {
        return this->array_[this->curr_size_ - 1];
    }

    // Deletion
    T dequeue() override {
        T temp = this->array_[curr_size_ - 1];
        this->array_[curr_size_ - 1] = 0;
        this->curr_size_ -= 1;
        return temp;
    }
    void PrintForward() {
        for (size_t i = 0; i < this->curr_size_; i++) {
            std::cout << this->array_[i] << std::endl;
        }
    }
    void PrintReverse() {
        for (size_t i = curr_size_; i < 0; --i) {
            std::cout << this->array_[i] << std::endl;
        }
    }

};
