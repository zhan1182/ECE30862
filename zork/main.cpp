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
    doc.parse<0>(text_nc);
    
	return EXIT_SUCCESS;
}
