#include "Value.h"

#include <iostream>
#include <stdexcept>


Value::Value(std::string word)
{
    //std::cout << "creating new Value with word: " << word << std::endl; // debug
    
    if(word.empty())
    {
        throw std::out_of_range("word == empty");
    }

    if(word.length() < 2)
    {
        throw std::out_of_range("word.length < 2");
    }

    this->word = word;
    prev = NULL;
}
// post: Value is properly initialised with word as value

void Value::print() const
{
    std::cout << word;

    if(prev != NULL)
    {
        std::cout << ", ";
        prev->print();
    }
}
// post: current value is printed to stdout