//
// Created by mihail on 09.11.2019.
//

#ifndef MYSTACKREALIZATION_NOCOPYABLESTACK_HPP
#define MYSTACKREALIZATION_NOCOPYABLESTACK_HPP

#include <iostream>
#include <StackException.hpp>

template <typename T>
struct Node{
    T value;
    Node<T> *prevElement = nullptr; // Указатель на предыдущий элемент стека
};

template <typename T>
class NoCopyableStack{
private:
    Node<T> *topElement = nullptr;
//    int count = 0; // Счётчик элементов стека. TODO 0 or 1?

public:

    explicit NoCopyableStack() = default;
    virtual ~NoCopyableStack() = default;
    NoCopyableStack(const NoCopyableStack &stack) = delete;
    NoCopyableStack &operator=(const NoCopyableStack &stack) = delete;
    NoCopyableStack(NoCopyableStack &&stack) noexcept = default;

    template <typename ... Args>
    void push_emplace(Args&&... value){
        auto* prevEl = topElement;
        topElement = new Node<T>{{std::forward<Args>(value)...},
                                 prevEl
                                };
    }

    void push(T&& value){
        auto* prevNode = topElement;
        topElement = new Node<T>{std::forward<T>(value), prevNode};
    }

    const T& head() const{
        if(!topElement){
            throw StackException("Stack is empty");
        }
        return topElement->value;
    }

    T pop(){
        if(!topElement){
            throw StackException("Stack is empty");
        }

        auto prevNode = topElement;
        topElement = topElement->prevElement;

        T value = std::move(prevNode->value);
        delete prevNode;
        return value;
    }
};

#endif //MYSTACKREALIZATION_NOCOPYABLESTACK_HPP
