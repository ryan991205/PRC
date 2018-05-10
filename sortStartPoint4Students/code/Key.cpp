#include "Key.h"

#include <iostream>
#include <stdexcept>

#define STRING_BEGIN 0
#define THIRD_CHAR 2


Key::Key()
{
    //std::cout << "creating new Key" << std::endl; // debug

    key = "";
    valueTail = NULL;
    prevKey = NULL;
}
// post: Key is properly initialised, however the key value
//       is illegal (empty)

Key::~Key()
{
    //std::cout << "deleting key" << std::endl; // debug
    
    Value* prev;
    while(valueTail != NULL)
    {
        prev = valueTail->getPrev();
        delete valueTail;
        valueTail = prev;
    }

    if(prevKey != NULL)
    {
        delete prevKey;
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

void Key::addValue(std::string word)
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

    //std::cout << "Key: " << key << " addValue() with word: " << word <<std::endl; // debug

    if(key.compare(word.substr(STRING_BEGIN, THIRD_CHAR)) == 0)
    {
        //std::cout << "word matches" << std::endl; // debug

        Value* prev = valueTail;

        valueTail = new Value(word);
        valueTail->setPrev(prev);

        //std::cout << "word matches\n" << std::endl; // debug
        return;
    }

    if(prevKey == NULL)
    {
        //std::cout << "test printing: " << std::endl;
        //print();
        //std::cout << '\n' << std::endl;

        //std::cout << "creating new key... "; // debug

        prevKey = new Key();
        prevKey->setText(word.substr(STRING_BEGIN, THIRD_CHAR));

        //std::cout << "done!" << std::endl; // debug
    }

    //std::cout << "loop" << std::endl;
    prevKey->addValue(word);
}
// post: a new word is added to the correct key:
//       - if the word fits in this key, a new value is added to the valuelist
//       - if the word doesn't fit in this key, addValue is called on the next key
//       - if no fitting key is found, a new key is made with this value in it

int Key::getListLength(Value* value)
{
    //std::cout << "Key::getListLength() called!" << std::endl;
    
    int counter = 0;

    while(value != NULL)
    {
        counter++;
        value = value->getPrev();
    }

    return counter;
}

Value* Key::merge(Value* a, Value* b)
{
    //std::cout << "Key::merge() called!" << std::endl;
    
    Value* newTail;
	//Base case: return the other half if  one of them is NULL
	if(a == NULL) return b;
	if(b == NULL) return a;
	
	//compare the value
	if(a->getText().compare(b->getText()) < 0)
    {
		newTail = a;							//assign the newHead to the Node has smaller value
		newTail->setPrev(merge(a->getPrev(), b));	//recall the functionto find the next Node
	}
	else
    {
		newTail = b;
		newTail->setPrev(merge(a, b->getPrev()));
	}
	
	return newTail;
}

Value* Key::sort(Value* tail)
{
    //std::cout << "Key::sort() called!" << std::endl;

    if(tail->getPrev() == NULL)
    {
        return tail;
    }

    Value* a;
    Value* b = tail;

    for(int i = 0; i < getListLength(tail) / 2; i++)
    {
        a = b;
        b = b->getPrev();
    }

    a->setPrev(NULL);
    a = tail;

    a = sort(a);
    b = sort(b);

    return merge(a, b);
}
// post: sorts all values that belong to this key

void Key::print() const
{
    std::cout << "Key: ";

    if(key.empty())
    {
        std::cout << "!empty string!";
    }
    else
    {
        std::cout << key;
    }
    
    if(valueTail != NULL)
    {
        std::cout << " -> ";
        valueTail->print();
    }
    
    std::cout << std::endl;

    if(prevKey != NULL)
    {
        prevKey->print();
    }
}
// post: all keys and values are recursively printed