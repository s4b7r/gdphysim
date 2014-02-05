/*
 * test.cpp
 *
 *  Created on: 05.02.2014
 *      Author: sieb
 */

#include <stdio.h>
#include "kissms/kissms.h"

int main(int argc, char **argv) {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(va, co);
	va->setName(na);
	co->setValue(4);
	kissms::ResultCode rc = eq->calculateFor(va);

	printf("%d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}



