#include "Key.h"

#include <iostream>
#include <stdexcept>

#define STRING_BEGIN 0
#define THIRD_CHAR 2


Key::Key()
{
    key = "";
    head = NULL;
    nextKey = NULL;
    prevKey = NULL;
}
// post: Key is properly initialised, however the key value
//       is illegal (empty)

Key::~Key()
{
    while(head != NULL)
    {
        Value* next = head->GetNext();
        delete head;
        head = next;
    }

    if(nextKey != NULL)
    {
        delete nextKey;
    }
}
// post: recursively deletes all keys and values

bool Key::SetText(std::string key)
{
    if(key.length() == 2)
    {
        this->key = key;
        return true;
    }

    return false;
};
// post: if key length equals 2 the key value is set and true is returned,
//       else key is ignored and false is returned

void Key::AddValue(std::string word)
{
    if(word.empty())
    {
        throw std::out_of_range("word == empty");
    }

    if(word.length() < 2)
    {
        throw std::out_of_range("word.length < 2");
    }

    if(key.compare(word.substr(STRING_BEGIN, THIRD_CHAR)))
    {
        Value* next = head;
        head = new Value(word);
        head->SetNext(next);
        next->SetPrev(head);
        return;
    }

    if(nextKey == NULL)
    {
        nextKey = new Key();
        nextKey->SetPrev(this);
        nextKey->SetText(word.substr(STRING_BEGIN, THIRD_CHAR));
    }

    nextKey->AddValue(word);
}
// post: a new word is added to the correct key:
//       - if the word fits in this key, a new value is added to the valuelist
//       - if the word doesn't fit in this key, addValue is called on the next key
//       - if no fitting key is found, a new key is made with this value in it

void Key::Sort()
{
    // todo: sort all values in key this key

    // end of todo

    if(nextKey != NULL)
    {
        nextKey->Sort();
    }
}
// post: sorts all values that belong to this key

void Key::Print() const
{
    std::cout << "Key: " << key;

    if(head != NULL)
    {
        std::cout << ' ';
        head->Print();
    }

    std::cout << '\n';

    if(nextKey != NULL)
    {
        nextKey->Print();
    }
}
// post: all keys and values are recursively printed