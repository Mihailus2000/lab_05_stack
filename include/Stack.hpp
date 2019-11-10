//
// Created by mihail on 05.11.2019.
//

#ifndef TEMPLATE_STACK_HPP
#define TEMPLATE_STACK_HPP

#include "StackException.hpp"

template <typename T>
struct NoCopyNode{
    T value;
    NoCopyNode<T> *prevElement = nullptr; // Указатель на предыдущий элемент стека
};

template <typename T>
class Stack{
private:


    NoCopyNode<T> *topElement = nullptr;
//    int count = 0; // Счётчик элементов стека. TODO 0 or 1?
public:
    Stack() = default;
    virtual ~Stack() = default;
    Stack(const Stack &stack) = delete;
    Stack &operator=(const Stack &stack) = delete;
    Stack(Stack &&stack) noexcept = default;


    void push(T&& value){
        auto* prevElem = topElement;
        topElement = new NoCopyNode<T>{std::forward<T>(value), prevElem,};
    }

    void push(const T& value){
        auto* prevElem = topElement;
        topElement = new NoCopyNode<T>{value, prevElem,};
    }
    void pop(){
        if(!topElement){
            throw StackException("Stack is empty");
        }

        topElement = topElement->prevElement;
    }
    const T& head() const{
        if (!topElement) {
            throw StackException("Stack is empty");
        }
        return topElement->value;
    }


};

#endif //TEMPLATE_STACK_HPP
