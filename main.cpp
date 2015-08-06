#include <iostream>
#include "Globals.h"
#include "Constants.h"
#include "Processing.h"
#include "HyperGraph/HyperGraph.h"
#include "HyperGraph/Instantiate.h"

int main() {
    //Fragment_T fragment("/Users/MatthewMcKay/ClionProjects/MEIXMLparser/test.xml");
    typedef std::vector<const char *> Files_T;
    Files_T files;
    files.push_back("/Users/MatthewMcKay/ClionProjects/MusicSynthesis_v2/music_tester2.xml");
    //files.push_back("/Users/MatthewMcKay/ClionProjects/XercesDeepNest/music_test.xml");
    //files.push_back("/Users/MatthewMcKay/ClionProjects/XercesDeepNest/music_test.xml");
    std::vector<SHP_T(Fragment_T)> fragments;
    Processing_T process(files);
    //process.PrintMusic();
    fragments = process.MakeFragments();
    for (auto it = fragments.begin(); it != fragments.end(); ++it){
        (*it)->GenerateBasis();
        Instantiate_T instantiate_t(*it);
        std::cout<<instantiate_t.graph.vertices.size()<<"\n\n";
    }
    std::cout << "\n\n************************\ntotal pointers = " << global_shpCt << '\n';
    return 0;
}