//
// Created by mihail on 09.11.2019.
//

#ifndef MYSTACKREALIZATION_NOCOPYABLESTACK_HPP
#define MYSTACKREALIZATION_NOCOPYABLESTACK_HPP

#include <iostream>

template <typename T>
class NoCopyableStack{
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
    explicit NoCopyableStack() = default;
    virtual  ~NoCopyableStack() = default;
    template <typename ... Args>
    void push_emplace(Args&&... value){
        T *newContainedElem = new T(std::forward<Args>(value)...);
        Node* newElem = new Node(std::move(*newContainedElem));
        newElem->prevElement = topElement;
        topElement = std::move(newElem);
    }
    void push(T&& value){

    }
    const T& head() const;
    T pop(){

    }
};

#endif //MYSTACKREALIZATION_NOCOPYABLESTACK_HPP
