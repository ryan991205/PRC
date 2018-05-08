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

        const std::string GetText() { return word; };
        // post: current value is returned

        void SetText(std::string value) { word = value; };
        // post: value is updated with new value

        Value* GetNext() { return nextValue; };
        // post: ponter to next value is returned

        void SetNext(Value* next) { nextValue = next; };
        // post: pointer to next value is set

        Value* GetPrev() { return prevValue; };
        // post: pointer to prev value is returned

        void SetPrev(Value* prev) { prevValue = prev; };
        // post: pointer to prev value is set

        void Print() const;
        // post: current value is printed to stdout

    private:
        std::string word;
        Value* nextValue;
        Value* prevValue;

        // private copy constructor and assignment operator to prevent making copies
        Value(const Value&) { /* do nothing */ };
        Value& operator= (const Value&) { return *this; };
};

#endif
