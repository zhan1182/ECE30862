#include <iostream>
#include <fstream>
#include <string>
#include "rapidxml/rapidxml.hpp"
using namespace std;
using namespace rapidxml;

#include "base.hh"
#include "room.hh"

int main(int argc, char ** argv)
{
    ifstream ifs("samples/sample.txt.xml");
    string text((istreambuf_iterator<char>(ifs)),
                    istreambuf_iterator<char>());
    
    //Use xml parser
    xml_document<> doc;
    //Cast const char* to non-const, don't try to modify it
    doc.parse<0>(const_cast<char *>(text.c_str()));
    cout << doc.first_node()->first_node()->first_node()->value() << endl;
    doc.first_node()->remove_first_node();
    cout << doc.first_node()->first_node()->first_node()->value()<< endl;
    
    return EXIT_SUCCESS;
}
