#include <iostream>
#include "Processing.h"

int main() {
    //Fragment_T fragment("/Users/MatthewMcKay/ClionProjects/MEIXMLparser/test.xml");
    typedef std::vector<const char *> Files_T;
    Files_T files;
    files.push_back("/Users/MatthewMcKay/ClionProjects/XercesDeepNest/music_test.xml");
    Processing_T process(files);
    process.PrintMusic();
    return 0;
}