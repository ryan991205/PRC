#include "FileStructure.cpp"


FileStructure::FileStructure()
{

}

void FileStructure::loadFile(std::string filename, Key& head)
{
    // todo: load new list

}
// post: if file with filename exists, its data is read, decoded and stored in a
//       proper key/value tree.

void FileStructure::saveFile(Key& head, std::string filename) const
{
    // todo: save current list

}
// post: if a file with filename can be created, head is recursively written it