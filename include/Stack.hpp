//
// Created by mihail on 05.11.2019.
//

#ifndef TEMPLATE_STACK_HPP
#define TEMPLATE_STACK_HPP

#include "StackException.hpp"

template <typename T>
class Stack{
private:
    struct Node{
        Node *prevElement; // Указатель на предыдущий элемент стека
        T value;
        Node() = default;
        Node(T val){
            value = val;
            prevElement = nullptr;
        }
    };

    Node *topElement = new Node();
    int count = 0; // Счётчик элементов стека. TODO 0 or 1?
public:
    Stack() = default;
    virtual ~Stack() = default;

    void push(T&& value){
        Node * newElement = new Node(std::forward<T>(value));
        if(count == 0)
            topElement = newElement;
        else{
            newElement->prevElement = topElement;
            topElement = newElement;
        }
        count++;
    }

    void push(const T& value){
        Node * newElement = new Node(value);
        if(count == 0)
            topElement = std::move(newElement);
        else{
            newElement->prevElement = topElement;
            topElement = std::move(newElement);
        }
        count++;
    }
    void pop(){
        if(count != 0){
            Node * temp = topElement;
            topElement = topElement->prevElement;
            delete temp;
            count--;
        }
        else{
            throw StackException("The stack is empty!\n\n");
        }
    }
    const T& head() const{
        return &topElement->value;
    }


};

#endif //TEMPLATE_STACK_HPP
