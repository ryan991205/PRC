#include <iostream>

#include "FileStructure.h"
#include "Key.h"


void SortKeys(Key* head)
{
    // todo: sort keys

}
// post: Sort all keys.

int main()
{
    FileStructure f;
    Key head;
    
    f.LoadFile("data/gibberish.bin", head);

    // next line is only to show what kind of data we're working with
    // remove this line to increase performance!
    head.Print();
    
    // sort all data
    // todo: call your sort method(s) here!
    SortKeys(&head);

    // save sorted data into a new file called sorted.bin
    f.SaveFile(head, "sorted.bin");
    
    return 0;
}
