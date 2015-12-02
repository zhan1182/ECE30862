#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#include "base.hh"
#include "room.hh"

int main(int argc, char ** argv)
{
	string s1 = "base";
	string s2 = "test";

	Base b(s1, s2);
	Room r(s1, s2, "exit");

	b.print();

	r.print();

	return EXIT_SUCCESS;
}