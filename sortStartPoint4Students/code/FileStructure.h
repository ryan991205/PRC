#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include "Key.h"
#include <string>

class FileStructure
{
    public:
        FileStructure();
        // post: FileStructure object is properly initialised
        virtual ~FileStructure();
        // empty virtual destructor
        
        void loadFile(std::string filename, Key& head);
        // post: if file with filename exists, its data is read, decoded and stored in a
        //       proper key/value tree.

        void saveFile(Key& head, std::string filename) const;
        // post: if a file with filename can be created, head is recursively written it

    private:
        // private copy constructor and assignment operator to prevent making copies
        FileStructure(const FileStructure&) { /* do nothing */ };
        FileStructure& operator= (const FileStructure&) { return *this; };
};

#endif
