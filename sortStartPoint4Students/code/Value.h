#ifndef VALUE_H
#define VALUE_H

#include <string>

class Value
{
    public:
        Value(std::string word);
        // post: Value is properly initialised with word as value
        virtual ~Value();
        // empty virtual destructor

        std::string getText() const;
        // post: current value is returned

        void setText(std::string value);
        // post: value is updated with new value

        Value* getPrev();
        // post: pointer to prev value is returned

        void setPrev(Value* prev);
        // post: pointer to prev value is set

        void print() const;
        // post: current value is printed to stdout

    private:
        std::string word;
        Value* prev;

        // private copy constructor and assignment operator to prevent making copies
        Value(const Value&) { /* do nothing */ };
        Value& operator= (const Value&) { return *this; };
};

#endif
