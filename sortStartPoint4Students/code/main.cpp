#include <iostream>
//#include <stdexcept>

#include "FileStructure.h"
#include "Key.h"


int getListLength(Key* key)
{
    int counter = 0;

    while(key != NULL)
    {
        counter++;
        key = key->getPrev();
    }

    return counter;
}

Key* merge(Key* a, Key* b)
{
    Key* newHead;
	//Base case: return the other half if  one of them is NULL
	if(a == NULL) return b;
	if(b == NULL) return a;
	
	//compare the value
	if(a->getText().compare(b->getText()) < 0)
    {
		newHead = a;							//assign the newHead to the Node has smaller value
		newHead->setPrev(merge(a->getPrev(), b));	//recall the functionto find the next Node
	}
	else
    {
		newHead = b;
		newHead->setPrev(merge(a, b->getPrev()));
	}
	
	return newHead;
}

Key* sort(Key* tail)
{
    if(tail->getPrev() == NULL)
    {
        return tail;
    }

    Key* a;
    Key* b = tail;

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

void sortValues(Key* key)
{
    while(key != NULL)
    {
        key->setValuePtr(key->sort(key->getValuePtr()));
        key = key->getPrev();
    }
}

int main()
{
    //std::cout << "Program start" << std::endl; // debug

    FileStructure f;
    Key* tail = new Key();

    //std::cout << "loading from data/gibberish.bin" << std::endl; // debug
    f.loadFile("data/gibberish.bin", *tail);

    /*// test data:
    tail->addValue("value");
    tail->addValue("hezlo");
    tail->addValue("tafel");
    tail->addValue("dikker");
    tail->addValue("dallo");
    tail->addValue("hexlo");
    tail->addValue("heylo");
    tail->addValue("tafel");
    tail->addValue("dikegex");
    tail->addValue("fuvcb");
    tail->addValue("dhfdbe");
    tail->addValue("hello");
    tail->addValue("fel");
    tail->addValue("feop");
    tail->addValue("fer");
    tail->addValue("zaag");
    tail->addValue("zeno");
    tail->addValue("xtye");
    tail->addValue("ytr");
    tail->addValue("ope");
    tail->addValue("mon");
    tail->addValue("nom");
    //*/

    //*// Remove first empty key
    Key* oldTail = tail;
    tail = tail->getPrev();
    oldTail->setPrev(NULL);
    delete oldTail;
    //oldTail = NULL;
    //*/

    // next lines are only to show what kind of data we're working with
    // remove these lines to increase performance!
    /*//
    std::cout << "\nBefore sort:\n"; // debug
    tail->print();
    std::cout << '\n' << std::endl; // debug
    //*/
    
    // sort all data
    // todo: call your sort method(s) here!
    //std::cout << "Sorting keys... " << std::endl; // debug
    tail = sort(tail);
    //std::cout << "done!" << std::endl; // debug

    //std::cout << "Sorting values in keys... " << std::endl; // debug
    sortValues(tail);
    //std::cout << "done!" << std::endl; // debug

    // next lines are only to show what kind of data we're working with
    // remove these lines to increase performance!
    /*//
    std::cout << "\nAfter sort:\n"; // debug
    tail->print();
    std::cout << '\n' << std::endl; // debug
    //*/

    // save sorted data into a new file called sorted.bin
    //std::cout << "Saving to sorted.bin" << std::endl; // debug
    f.saveFile(*tail, "sorted.bin");

    delete tail;

    //std::cout << "Program done" << std::endl; // debug
    
    return 0;
}
