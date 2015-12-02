#ifndef BASE_H_
#define BASE_H_


#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Base
{
	string name;
	string description;
	int status;
public:
	Base();
	~Base();
	void print();
};


#endif