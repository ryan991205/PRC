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
}
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
        firstLowerOrEqualValue = GetFirstLowerOrEqualValue(currentValue);

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
    std::cout << "Key: " << key;

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

    Value* prevValue = value->GetPrev();

    while((prevValue != NULL) && (prevValue->GetText() > value->GetText()))
    {
        prevValue = prevValue->GetPrev();
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

    Value* prevValue = value->GetPrev();
    Value* nextValue = value->GetNext();

    if(prevValue != NULL)
    {
        prevValue->SetNext(nextValue);
    }

    if(nextValue != NULL)
    {
        nextValue->SetPrev(prevValue);
    }

    /*// probably not necessary but clean
    value->SetPrev(NULL);
    value->SetNext(NULL);
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

    Value* newNextValue = newPrevValue->GetNext();

    value->SetPrev(newPrevValue);
    value->SetNext(newNextValue);

    newPrevValue->SetPrev(value);
    if(newPrevValue != NULL)
    {
        newPrevValue->SetNext(value);
    }
}
// post: