//
// Created by mihail on 05.11.2019.
//

#ifndef MYSTACKREALIZATION_STACKEXCEPTION_HPP
#define MYSTACKREALIZATION_STACKEXCEPTION_HPP

#include <exception>
#include <itclIntDecls.h>
#include <string>


class StackException : public std::exception {
public:
    StackException(std::string const &message) : msg(message){}
    virtual char const *what() const noexcept {
//        std::cerr << msg << std::endl;
        return msg.c_str();
    }

private:
    std::string msg;
};


#endif //MYSTACKREALIZATION_STACKEXCEPTION_HPP
