//============================================================================
// Name        : Phystest.cpp
// Author      : fsd
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "physic/physic.h"
#include "kissms/kissms.h"

using std::cout;
using std::endl;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	Solid test1(1,2,3);
	cout 		<< test1.getMass()
				<< " "
				<< test1.getCenter().getArgument(0)->getQuantity()
				<< " "
				<< test1.getCenter().getArgument(1)->getQuantity()
				<< " "
				<< test1.getCenter().getArgument(2)->getQuantity() << endl;
	return 0;
}
