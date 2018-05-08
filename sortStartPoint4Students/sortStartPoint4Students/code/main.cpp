#include <iostream>
//#include <stdexcept>

#include "FileStructure.h"
#include "Key.h"


Key* GetFirstHigherOrEqualKey(Key* key)
{
    /*// probably not necessary but clean
    if(key == NULL)
    {
        throw std::logic_error("key == NULL");
    }
    //*/

    Key* prevKey = key->GetPrev();

    while((prevKey != NULL) && (prevKey->GetText() > key->GetText())) // !!!
    {
        prevKey = prevKey->GetPrev();
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

    Key* prevKey = key->GetPrev();
    Key* nextKey = key->GetNext();

    if(prevKey != NULL)
    {
        prevKey->SetNext(nextKey);
    }

    if(nextKey != NULL)
    {
        nextKey->SetPrev(prevKey);
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

    Key* newPrevKey = newNextKey->GetPrev();

    key->SetPrev(newPrevKey);
    key->SetNext(newNextKey);

    newNextKey->SetPrev(key);
    if(newPrevKey != NULL)
    {
        newPrevKey->SetNext(key);
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

    Key* currentKey = head->GetNext();
    Key* next = NULL;
    Key* firstHigherOrEqualKey = NULL;

    while(currentKey != NULL)
    {
        currentKey->Sort(); // seperate thread
        next = currentKey->GetNext();

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
    FileStructure f;
    Key head;
    
    f.LoadFile("data/gibberish.bin", head);

    // next lines are only to show what kind of data we're working with
    // remove these lines to increase performance!
    //*//
    std::cout << "\nBefore sort:\n";
    head.Print();
    std::cout << '\n' << std::endl;
    //*/
    
    // sort all data
    // todo: call your sort method(s) here!
    SortKeys(&head);

    // next lines are only to show what kind of data we're working with
    // remove these lines to increase performance!
    //*//
    std::cout << "\nBefore sort:\n";
    head.Print();
    std::cout << '\n' << std::endl;
    //*/

    // save sorted data into a new file called sorted.bin
    f.SaveFile(head, "sorted.bin");
    
    return 0;
}
