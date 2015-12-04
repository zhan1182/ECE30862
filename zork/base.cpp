

using namespace std;

#include "base.hh"


Base::Base(string Name, string Description, string Status):name(Name), description(Description), status(Status)
{
}

Base::~Base()
{

}


void Base::print()
{
	cout << "Name: " << name << " " << "Description: " << description << endl;
}

string Base::getName()
{
	return name;
}

string Base::getDes()
{
	return description;
}

string Base::getStatus()
{
	return status;
}

