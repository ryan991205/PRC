#include "Key.h"

#include <iostream>
#include <stdexcept>

#define STRING_BEGIN 0
#define THIRD_CHAR 2


Key::Key()
{
    //std::cout << "creating new Key" << std::endl; // debug

    key = "";
    head = NULL;
    nextKey = NULL;
    prevKey = NULL;
}
// post: Key is properly initialised, however the key value
//       is illegal (empty)

Key::~Key()
{
    //std::cout << "deleting key" << std::endl; // debug
    
    while(head != NULL)
    {
        Value* next = head->getNext();
        delete head;
        head = next;
    }

    if(nextKey != NULL)
    {
        delete nextKey;
    }
}
// post: recursively deletes all keys and values

bool Key::setText(std::string key)
{
    //std::cout << "Adding keyword: " << key << " to new key" << std::endl; // debug

    if(key.length() == 2)
    {
        this->key = key;
        return true;
    }

    return false;
}
// post: if key length equals 2 the key value is set and true is returned,
//       else key is ignored and false is returned

void Key::AddValue(std::string word)
{
    /*//
    if(word.empty())
    {
        throw std::out_of_range("word == empty");
    }

    if(word.length() < 2)
    {
        throw std::out_of_range("word.length < 2");
    }
    //*/

    //std::cout << "Key: " << key << " AddValue() with word: " << word <<std::endl; // debug

    //if(key.empty())
    //{
    //    key = word.substr(STRING_BEGIN, THIRD_CHAR);
    //}

    if(key.compare(word.substr(STRING_BEGIN, THIRD_CHAR)) == 0)
    {
        //std::cout << "word matches" << std::endl; // debug

        Value* next = head;

        head = new Value(word);
        head->setNext(next);

        if(next != NULL)
        {
            next->setPrev(head);
        }

        std::cout << "word matches" << std::endl; // debug
        return;
    }

    if(nextKey == NULL)
    {
        nextKey = new Key();
        nextKey->setPrev(this);
        nextKey->setText(word.substr(STRING_BEGIN, THIRD_CHAR));

        //std::cout << "creating new key" << std::endl; // debug
    }

    //std::cout << "loop" << std::endl;
    nextKey->AddValue(word);
}
// post: a new word is added to the correct key:
//       - if the word fits in this key, a new value is added to the valuelist
//       - if the word doesn't fit in this key, addValue is called on the next key
//       - if no fitting key is found, a new key is made with this value in it

void Key::Sort()
{
    /*// probably not necessary but clean
    if(currentValue == NULL)
    {
        throw std::logic_error("currentValue == null");
    }
    //*/

    Value* currentValue = head;
    Value* next = NULL;
    Value* firstLowerOrEqualValue = NULL;

    while(currentValue != NULL)
    {
        firstLowerOrEqualValue = GetFirstHigherOrEqualValue(currentValue);

        if(firstLowerOrEqualValue != NULL)
        {
            DisconnectValue(currentValue);
            InsertAfter(currentValue, firstLowerOrEqualValue);
        }

        currentValue = next;
    }
}
// post: sorts all values that belong to this key

void Key::Print() const
{
    std::cout << "Key: ";

    if(key == "")
    {
        std::cout << "!empty string!";
    }
    else
    {
        std::cout << key;
    }

    if(head != NULL)
    {
        std::cout << " -> ";
        head->Print();
    }

    std::cout << std::endl;

    if(nextKey != NULL)
    {
        nextKey->Print();
    }
}
// post: all keys and values are recursively printed

Value* Key::GetFirstHigherOrEqualValue(Value* value)
{
    /*// probably not necessary but clean
    if(value == NULL)
    {
        throw std::logic_error("value == NULL");
    }
    //*/

    Value* prevValue = value->getPrev();

    while((prevValue != NULL) && (prevValue->getText() > value->getText()))
    {
        prevValue = prevValue->getPrev();
    }

    return prevValue;
}
// post: 

void Key::DisconnectValue(Value* value)
{
    /*// probably not necessary but clean
    if(value == NULL)
    {
        throw std::logic_error("value == NULL");
    }
    //*/

    Value* prevValue = value->getPrev();
    Value* nextValue = value->getNext();

    if(prevValue != NULL)
    {
        prevValue->setNext(nextValue);
    }

    if(nextValue != NULL)
    {
        nextValue->setPrev(prevValue);
    }

    /*// probably not necessary but clean
    value->setPrev(NULL);
    value->setNext(NULL);
    //*/
}
// post: 

void Key::InsertAfter(Value* value, Value* newPrevValue)
{
    /*// probably not necessary but clean
    if(value == NULL)
    {
        throw std::logic_error("value == NULL");
    }

    if(newPrevValue == NULL)
    {
        throw std::logic_error("newPrevValue == NULL");
    }
    //*/

    Value* newNextValue = newPrevValue->getNext();

    value->setPrev(newPrevValue);
    value->setNext(newNextValue);

    newPrevValue->setPrev(value);
    if(newPrevValue != NULL)
    {
        newPrevValue->setNext(value);
    }
}
// post: