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

void test4() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Multiplication *mu = new kissms::Multiplication();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co1 = new kissms::Constant();
	kissms::Constant *co2 = new kissms::Constant();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(mu, co2);
	mu->setArguments(va, co1);
	va->setName(na);
	co1->setValue(7);
	co2->setValue(42);

	kissms::ResultCode rc = eq->calculateFor(va);

	printf("%d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

void test5() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Reciprocal *re = new kissms::Reciprocal();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(re, co);
	re->setArgument(va);
	va->setName(na);
	co->setValue(0.5);

	kissms::ResultCode rc = eq->calculateFor(va);

	printf("%d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

void test6() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Negation *ne = new kissms::Negation();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(ne, co);
	ne->setArgument(va);
	va->setName(na);
	co->setValue(0.5);

	kissms::ResultCode rc = eq->calculateFor(va);

	printf("%d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

void test7() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Sinus *sin = new kissms::Sinus();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(sin, co);
	sin->setArgument(va);
	va->setName(na);
	co->setValue(1);

	kissms::ResultCode rc = eq->calculateFor(va);

	printf("%d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

int main(int argc, char **argv) {

	/*test1();
	printf("\n");
	test2();
	printf("\n");
	test3();
	printf("\n");
	test4();
	printf("\n");
	test5();
	printf("\n");
	test6();
	printf("\n");*/
	test7();

	return 0;

}




