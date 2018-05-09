#ifndef KEY_H
#define KEY_H

#include <iostream>

#include "Value.h"

class Key
{
    public:
        Key();
        // post: Key is properly initialised, however the key value
        //       is illegal (empty)
        ~Key();
        // post: recursively deletes all keys and values

        bool setText(std::string key);
        // post: if key length equals 2 the key value is set and true is returned,
        //       else key is ignored and false is returned

        const std::string getText() { return key; };
        // post: current key value is returned

        Value* getHead() { return head; };
        // post: pointer to this key's first value is returned
        
        void setHead(Value* head) { this->head = head; };
        // post: pointer to this key's first value is set

        void setNext(Key* next) { nextKey = next; };
        // post: ponter to the next key is returned

        Key* getNext() { return nextKey; };
        // post: pointer to the next key is set
        
        void setPrev(Key* prev) { prevKey = prev; };
        // post: pointer to the prev key is set
        
        Key* getPrev() { return prevKey; };
        // post: pointer to the prev key is returned

        void AddValue(std::string word);
        // post: a new word is added to the correct key:
        //       - if the word fits in this key, a new value is added to the valuelist
        //       - if the word doesn't fit in this key, addValue is called on the next key
        //       - if no fitting key is found, a new key is made with this value in it

        void Sort();
        // post: sorts all values that belong to this key

        void Print() const;
        // post: all keys and values are recursively printed
        
    private:
        std::string key;
        Value* head;
        Key* nextKey;
        Key* prevKey;

        Value* GetFirstHigherOrEqualValue(Value* value);
        // post: 

        void DisconnectValue(Value* value);
        // post: 

        void InsertAfter(Value* value, Value* newPrevValue);
        // post: 
        
        // private copy constructor and assignment operator to prevent making copies
        Key(const Key&) { /* do nothing */ };
        Key& operator= (const Key&) { return *this; };
};

#endif
