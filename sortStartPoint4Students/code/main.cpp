#include <iostream>
//#include <stdexcept>

#include "FileStructure.h"
#include "Key.h"


Key* GetFirstHigherOrEqualKey(Key* key)
{
    /*// probably not necessary but clean
    if(key == NULLg
    {
        throw std::logic_error("key == NULL");
    }
    //*/

    Key* prevKey = key->getPrev();

    while((prevKey != NULL) && (prevKey->getText().compare(key->getText()) <0)) // !!!
    {
        prevKey = prevKey->getPrev();
    }

    return prevKey;
}
// post: Function loops back through list to return the first key in the list that is higher or eqaul to the given key.
//       Returns NULL if the given key is has the smallets value in the list.

void DisconnectKey(Key* key)
{
    /*// probably not necessary but clean
    if(key == NULL)
    {
        throw std::logic_error("key == NULL");
    }
    //*/

    Key* prevKey = key->getPrev();
    Key* nextKey = key->getNext();

    if(prevKey != NULL)
    {
        prevKey->setNext(nextKey);
    }

    if(nextKey != NULL)
    {
        nextKey->setPrev(prevKey);
    }

    /*// probably not necessary but clean
    key->SetPrev(NULL);
    key->SetNext(NULL);
    //*/
}
// post: Disconnects key from list and links the prev and next keys to each other.

void InsertBefore(Key* key, Key* newNextKey)
{
    /*// probably not necessary but clean
    if(key == NULL)
    {
        throw std::logic_error("key == NULL");
    }

    if(newNextKey == NULL)
    {
        throw std::logic_error("newNextKey == NULL");
    }
    //*/

    Key* newPrevKey = newNextKey->getPrev();

    key->setPrev(newPrevKey);
    key->setNext(newNextKey);

    newNextKey->setPrev(key);
    if(newPrevKey != NULL)
    {
        newPrevKey->setNext(key);
    }
}
// post: Inserts key in front of other key.

void SortKeys(Key* head)
{
    /*// probably not necessary but clean
    if(currentKey == NULL)
    {
        throw std::logic_error("currentKey == null");
    }
    //*/

    Key* currentKey = head->getNext();
    Key* next = NULL;
    Key* firstHigherOrEqualKey = NULL;

    while(currentKey != NULL)
    {
        currentKey->Sort(); // seperate thread
        next = currentKey->getNext();

        firstHigherOrEqualKey = GetFirstHigherOrEqualKey(currentKey);

        if(firstHigherOrEqualKey != NULL)
        {
            DisconnectKey(currentKey);
            InsertBefore(currentKey, firstHigherOrEqualKey);
        }

        currentKey = next;
    }
}
// post: Sort all keys. Returns new head.

int main()
{
    std::cout << "Program start" << std::endl; // debug

    FileStructure f;
    Key head;

    std::cout << "loading from data/gibberish.bin" << std::endl; // debug
    
    //f.loadFile("data/gibberish.bin", head);

    //test data:
    head.AddValue("value");
    head.AddValue("hello");
    head.AddValue("tafel");
    head.AddValue("dikkeneger");
    head.AddValue("dallo");
    head.AddValue("hello");
    head.AddValue("hello");
    head.AddValue("tafel");
    head.AddValue("dikkenegex");
    head.AddValue("fuvcb");
    head.AddValue("dhfdbe");
    head.AddValue("hello");
    head.AddValue("fel");
    head.AddValue("feop");
    head.AddValue("fer");
     head.AddValue("zaag");
    head.AddValue("zeno");
    head.AddValue("xtye");
    head.AddValue("ytr");
    head.AddValue("ope");
    head.AddValue("mon");
    head.AddValue("nom");

    // next lines are only to show what kind of data we're working with
    // remove these lines to increase performance!
    //*//
    std::cout << "\nBefore sort:\n"; // debug
    head.Print();
    std::cout << '\n' << std::endl; // debug
    //*/
    
    // sort all data
    // todo: call your sort method(s) here!
    std::cout << "Sorting keys and values" << std::endl; // debug
    SortKeys(&head);

    // next lines are only to show what kind of data we're working with
    // remove these lines to increase performance!
    //*//
    std::cout << "\nAfter sort:\n"; // debug
    head.Print();
    std::cout << '\n' << std::endl; // debug
    //*/

    // save sorted data into a new file called sorted.bin
    std::cout << "Saving to sorted.bin" << std::endl; // debug
    f.saveFile(head, "sorted.bin");

    std::cout << "Program done" << std::endl; // debug
    
    return 0;
}
