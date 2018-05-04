#ifndef KEY_H
#define KEY_H

#include "Value.h"

class Key
{
    public:
        Key();
        // post: Key is properly initialised, however the key value
        //       is illegal (empty)

        virtual ~Key();
        // post: recursively deletes all keys and values
        
        std::string getText() const;
        // post: current key value is returned
        
        bool setText(std::string key);
        // post: if key length equals 2 the key value is set and true is returned,
        //       else key is ignored and false is returned

        void addValue(std::string word);
        // post: a new word is added to the correct key:
        //       - if the word fits in this key, a new value is added to the valuelist
        //       - if the word doesn't fit in this key, addValue is called on the next key
        //       - if no fitting key is found, a new key is made with this value in it
        
        Value* getValuePtr();
        // post: pointer to this key's first value is returned
        
        void setValuePtr(Value* value);
        // post: pointer to this key's first value is set
        
        void setPrev(Key* prev);
        // post: pointer to the prev key is set
        
        Key* getPrev();
        // post: pointer to the prev key is returned

        void print() const;
        // post: all keys and values are recursively printed
        
    private:
        std::string key;
        Value* valueTail;
        Key* prevKey;
        
        // private copy constructor and assignment operator to prevent making copies
        Key(const Key&) { /* do nothing */ };
        Key& operator= (const Key&) { return *this; };
};

#endif
