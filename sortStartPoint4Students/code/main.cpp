#include <iostream>

#include "FileStructure.h"
#include "Key.h"

int main()
{
    FileStructure f;
    Key head;
    
    f.loadFile("data/gibberish.bin", head);

    // next line is only to show what kind of data we're working with
    // remove this line to increase performance!
    head.print();
    
    // sort all data
    // todo: call your sort method(s) here!
    

    // save sorted data into a new file called sorted.bin
    f.saveFile(head, "sorted.bin");
    
    return 0;
}
