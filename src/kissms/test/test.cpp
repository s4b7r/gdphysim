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
	eq->calculateFor(va);

	printf("a=38\n");

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

	eq->calculateFor(va);

	printf("a+4=0\n");

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

	ne->setArgument(co);
	va->setName(na);
	co->setValue(4);
	co2->setValue(0);

	eq->calculateFor(va);

	printf("a+(-4)=0\n");

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

	eq->calculateFor(va);

	printf("a*7=42\n");

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

	eq->calculateFor(va);

	printf("1/a=0.5\n");

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

	eq->calculateFor(va);

	printf("-a=0.5\n");

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

	eq->calculateFor(va);

	printf("sin(a)=1\n");

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

void test8() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Sinus *sin1 = new kissms::Sinus();
	kissms::Cosinus *cos1 = new kissms::Cosinus();
	kissms::Sinus *sin2 = new kissms::Sinus();
	kissms::Cosinus *cos2 = new kissms::Cosinus();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();
	kissms::Multiplication *mu1 = new kissms::Multiplication();
	kissms::Multiplication *mu2 = new kissms::Multiplication();
	kissms::Addition *add = new kissms::Addition();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;

	eq->setArguments(add, va);
	add->setArguments(mu1, mu2);
	mu1->setArguments(sin1, sin2);
	mu2->setArguments(cos1, cos2);
	sin1->setArgument(co);
	sin2->setArgument(co);
	cos1->setArgument(co);
	cos2->setArgument(co);
	co->setValue(1);
	va->setName(na);

	eq->calculateFor(va);

	printf("sin(1)*sin(1)+cos(1)*cos(1)=a\n");

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);

}

void test9() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Vector *vec1 = new kissms::Vector();
	kissms::Vector *vec2 = new kissms::Vector();
	kissms::Constant *co1 = new kissms::Constant();
	kissms::Constant *co2 = new kissms::Constant();
	kissms::Constant *co3 = new kissms::Constant();
	kissms::Variable *var1 = new kissms::Variable();
	kissms::Variable *var2 = new kissms::Variable();
	kissms::Variable *var3 = new kissms::Variable();

	char *na1 = (char*) malloc(sizeof(char) * 2);
	na1[0] = 'a';
	na1[1] = 0;
	char *na2 = (char*) malloc(sizeof(char) * 2);
	na2[0] = 'b';
	na2[1] = 0;
	char *na3 = (char*) malloc(sizeof(char) * 2);
	na3[0] = 'c';
	na3[1] = 0;

	eq->setArguments(vec1, vec2);
	vec1->setArgument(0, var1);
	vec1->setArgument(1, var2);
	vec1->setArgument(2, var3);
	vec2->setArgument(0, co1);
	vec2->setArgument(1, co2);
	vec2->setArgument(2, co3);
	var1->setName(na1);
	var2->setName(na2);
	var3->setName(na3);
	co1->setValue(0.5);
	co2->setValue(1.8);
	co3->setValue(42);

	eq->calculateFor(var1);
	eq->calculateFor(var2);
	eq->calculateFor(var3);

	printf("(a, b, c) = (0.5, 1.8, 42)\n");

	double value1 = -42;
	value1 = var1->getQuantity();
	printf("%f", value1);
	double value2 = -42;
	value2 = var2->getQuantity();
	printf("%f", value2);
	double value3 = -42;
	value3 = var3->getQuantity();
	printf("%f", value3);

}

int main(int argc, char **argv) {

	//test1();
	printf("\n\n");
	//test2();
	printf("\n\n");
	//test3();
	printf("\n\n");
	//test4();
	printf("\n\n");
	test5();
	printf("\n\n");
	//test6();
	printf("\n\n");
	//test7();
	printf("\n\n");
	//test8();
	printf("\n\n");
	//test9();

	return 0;

}




