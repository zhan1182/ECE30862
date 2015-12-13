#ifndef CONDITION_H_
#define CONDITION_H_

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class Condition
{
	string object;
	string owner;
	string has;
	string status;

public:
	Condition(string Object, string Owner, string Has, string Status);
	virtual ~Condition();
	virtual void print();
	string getObject();
	string getOwner();
	string getHas();
	string getStatus();

	void setObject(string Object);
	void setOwner(string Owner);
	void setHas(string Has);
	void setStatus(string Status);

	bool has_exist();

};

#endif