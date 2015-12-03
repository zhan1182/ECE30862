#include <iostream>
#include <stdlib.h>
#include <string>
#include "rapidxml/rapidxml.hpp"
using namespace std;

#include "base.hh"
#include "room.hh"

int main(int argc, char ** argv)
{
    ifstream ifs(argv[1]);
    string text((istreambuf_iterator<char>(ifs)),
                    istreambuf_iterator<char>());
    
    //Use xml parser
    xml_document<> doc;
    //Cast const char* to non-const, don't try to modify it
    doc.parse<0>(const_cast<char *>(text_c_str()));
    
    return EXIT_SUCCESS;
}
