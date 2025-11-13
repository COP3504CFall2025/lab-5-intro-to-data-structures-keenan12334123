#pragma once

#include <cstddef>
#include <iostream>
#include <ostream>
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
    ABDQ() {
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    ABDQ(const ABDQ& other): data_(new T[other.capacity_]), capacity_(other.capacity_), front_(other.back_), back_(other.back_), size_(other.curr_size_) {
        for (int i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept : capacity_(other.capacity_), front_(other.front_), back_(other.back_), size_(other.size_), data_(other.data_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.capacity_ = 4;
    }

    ABDQ& operator=(const ABDQ& other){
        if (this == &other) return *this;
        T* new_arr = new T[other.capacity_];
        delete[] this->data_;

        this->data_ = new_arr;
        this->capacity_ = (other.capacity_);
        this->curr_size_ = (other.size_);
        this->front_ = (other.front_);
        this->back_ = (other.back_);
        for (int i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] this->data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->data_ = other.data_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        other.data_ =nullptr;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.capacity_ = 4;

        return *this;
    }
    ~ABDQ() {
        delete[] this->data_;
        this->capacity_ = 1;
        this->size_ = 0;
        this->front_ = 0;
        this->back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        T* tempArray;
        if (this->size_ == this->capacity_) {
            tempArray = new T[this->capacity_ * 2];
            this->capacity_ *= 2;
        }
        else {
            tempArray = new T[this->capacity_];
        }
        for (int i = 0; i < back_; i++) {
            tempArray[i] = this->data_[i];
        }
        tempArray[front_] = item;
        for (size_t i = front_ + 1; i < this->size_; ++i) {
            tempArray[i] = this->data_[i];
        }
        delete[] this->data_;
        this->data_ = tempArray;
        this->size_ += 1;
        if (this->back_ + 1 != this->size_ and this->back_ + 1 != front_) {
            back_ += 1;
        }
    }

    void pushBack(const T& item) override {
        T* tempArray;
        if (this->size_ == this->capacity_) {
            tempArray = new T[this->capacity_ * 2];
            this->capacity_ *= 2;
        }
        else {
            tempArray = new T[this->capacity_];
        }

        if (this->back_ < this->front_) {
            for (size_t i = front_; i < this->size_; ++i) {
                tempArray[i + 1] = this->data_[i];
            }
            tempArray[front_] = item;
            for (int i = 0; i < back_; i++) {
                tempArray[i + 1] = this->data_[i];
            }
        }
        else {
            for (int i = 0; i <= back_; i++) {
                tempArray[i] = this->data_[i];
            }
            tempArray[back_ + 1] = item;
        }
        back_ += 1;

        delete[] this->data_;
        this->data_ = tempArray;
        this->size_ += 1;
        if (this->front_ > this->back_) {
            front_ += 1;
        }
    }

    // Deletion
    T popFront() override {
        if (this->size_ == 0) {
            throw std::runtime_error("Empty queue");
        }
        else {
            T* temp = new T[this->capacity_];
            T test = this->data_[front_];
            for (size_t i = front_; i < this->size_; ++i) {
                if (i == this->size_) {
                    i = 0;
                }
                if (i == back_) {
                    temp[i] = this->data_[i];
                    break;
                }
                temp[i] = this->data_[i];
            }
            delete[] this->data_;
            this->data_ = temp;

            if (this->size_ * 2 < this->capacity_ && this-> capacity_ > 1) {
                this->capacity_ /= 2;
            }

            if (front_ + 1 != this->size_) {
                front_ += 1;

            }
            else if (data_[0] == test) {
                front_ = 0;
                back_ = 0;
            }
            else {
                front_ = 0;
            }

            this->size_ -= 1;
            return test;
        }
    }

    T popBack() override {
        if (this->size_ == 0) {
            throw std::runtime_error("Empty queue");
        }
        else {
            T* temp = new T[this->capacity_];
            T test = this->data_[back_];
            for (size_t i = front_; i < this->size_; ++i) {
                if (i == this->size_) {
                    i = 0;
                }
                if (i == back_) {
                    break;
                }
                temp[i] = this->data_[i];
            }
            delete[] this->data_;
            this->data_ = temp;
            this->size_ -= 1;

            if (this->size_ * 2 < this->capacity_ && this-> capacity_ > 1) {
                this->capacity_ /= 2;
            }
            if (back_ != 0 ) {
                back_ -= 1;
            }
            else {
                if (front_ != this->size_) {
                    back_ = this->size_ - 1;
                }
            }
            return test;
        }
    }

    // Access
    const T& front() const override {
        return this->data_[this->front_];
    }
    const T& back() const override {
        return this->data_[this->back_];
    }
    void PrintForward() {
        for (std::size_t i = front_; i < this->size_; ++i) {
            if (i == this->size_) {
                i = 0;
            }
            if (i == back_) {
                std::cout << this->data_[i] << std::endl;
                break;
            }
            std::cout << this->data_[i] <<std::endl;
        }
    }
    void PrintReverse() {
        for (std::size_t i = back_; i < this->size_; --i) {
            if (i == -1) {
                i = size_ - 1;
            }
            if (i == front_) {
                std::cout << this->data_[i] << std::endl;
                break;
            }
            std::cout << this->data_[i] <<std::endl;
        }
    }
    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }
};
