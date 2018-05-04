#include "Value.h"


Value::Value(std::string word)
{
    if(word::Length() < 2)
    {
        return; // exception
    }

    this->word = word;
    nextValue = NULL;
    prevValue = NULL;
}

void Value::Print() const
{

}