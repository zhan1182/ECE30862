
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

#include "base.hh"


Base::Base(string Name, string Description):name(Name), description(Description)
{
	status = "";
}

Base::~Base()
{
	
}


void Base::print()
{
	cout << "Name: " << name << " " << "Description: " << description << endl;
}