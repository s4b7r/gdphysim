/*
 * test.cpp
 *
 *  Created on: 05.02.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

void test1() {
	kissms::Equation *eq = new kissms::Equation();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(va, co);
	va->setName(na);
	co->setValue(38);
	kissms::ResultCode rc = eq->calculateFor(va);

	printf("%d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

void test2() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();
	kissms::Addition *ad = new kissms::Addition();
	kissms::Constant *co2 = new kissms::Constant();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(ad, co2);
	ad->setArguments(va, co);

	va->setName(na);
	co->setValue(4);
	co2->setValue(0);

	kissms::ResultCode rc = eq->calculateFor(va);

	printf("%d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

void test3() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();
	kissms::Addition *ad = new kissms::Addition();
	kissms::Constant *co2 = new kissms::Constant();
	kissms::Negation *ne = new kissms::Negation();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(ad, co2);
	ad->setArguments(va, ne);
	//ad->setArguments(va, co);

	ne->setArgument(co);
	va->setName(na);
	co->setValue(4);
	co2->setValue(0);

	kissms::ResultCode rc = eq->calculateFor(va);

	printf("%d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

int main(int argc, char **argv) {

	test1();
	printf("\n\n");
	test2();
	printf("\n\n");
	test3();

	return 0;

}




