
using namespace std;

#include "trigger.hh"

Trigger::Trigger(Condition CDT, string Type):
cdt(CDT), type(Type)
{

}

Trigger::~Trigger()
{


}

void Trigger::print()
{
	cout << "Object: " << cdt.getObject() << endl;
	cout << "Status: " << cdt.getStatus() << endl;
}