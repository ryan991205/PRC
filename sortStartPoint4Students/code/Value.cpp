#include "Value.h"

#include <iostream>
#include <stdexcept>


Value::Value(std::string word)
{
    if(word.empty())
    {
        throw std::out_of_range("word == empty");
    }

    if(word.length() < 2)
    {
        throw std::out_of_range("word.length < 2");
    }

    this->word = word;
    nextValue = NULL;
    prevValue = NULL;
}
// post: Value is properly initialised with word as value

void Value::Print() const
{
    std::cout << word;

    if(nextValue != NULL)
    {
        std::cout << ", ";
        nextValue->Print();
    }
}
// post: current value is printed to stdout