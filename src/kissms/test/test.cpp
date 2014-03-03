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
	printf("\n=%s", va->getQuality().c_str());

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
	printf("\n=%s", va->getQuality().c_str());

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
	printf("\n=%s", va->getQuality().c_str());

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
	printf("\n=%s", va->getQuality().c_str());

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
	printf("\n=%s", va->getQuality().c_str());

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
	printf("\n=%s", va->getQuality().c_str());

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
	printf("\n=%s", va->getQuality().c_str());

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
	printf("\n=%s", va->getQuality().c_str());

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
	printf("%f\t", value1);
	double value2 = -42;
	value2 = var2->getQuantity();
	printf("%f\t", value2);
	double value3 = -42;
	value3 = var3->getQuantity();
	printf("%f", value3);

	printf("\n%s\t%s\t%s", var1->getQuality().c_str(), var2->getQuality().c_str(), var3->getQuality().c_str());

}

void test10() {
	kissms::Equation *eq = new kissms::Equation();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co = new kissms::Constant();

	char *na = (char*) malloc(sizeof(char) * 2);
	na[0] = 'a';
	na[1] = 0;
	char *val = (char*) malloc(sizeof(char) * 2);
	val[0] = 'x';
	val[1] = 0;

	eq->setArguments(va, co);
	va->setName(na);
	co->setValue(val);
	kissms::ResultCode rc = eq->calculateFor(va);

	printf("a=x\n");
	printf("RC: %d\n", rc);

	double value = -42;
	value = va->getQuantity();

	printf("%f", value);
	printf("\n=%s", va->getQuality().c_str());

}

void test11() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Vector *vec1 = new kissms::Vector();
	kissms::Vector *vec2 = new kissms::Vector();
	kissms::Variable *var1 = new kissms::Variable();
	kissms::Variable *var2 = new kissms::Variable();
	kissms::Constant *con1 = new kissms::Constant();
	kissms::Constant *con0 = new kissms::Constant();

	eq->setArguments(vec1, vec2);
	vec1->setArgument(0, var1);
	vec1->setArgument(1, var2);
	vec1->setArgument(2, con0);
	vec2->setArgument(0, var2);
	vec2->setArgument(1, con1);
	vec2->setArgument(2, con0);
	con1->setValue(5);

	char *var1n = (char*) malloc(sizeof(char) * 2);
	var1n[0] = 'x';
	var1n[1] = 0;
	char *var2n = (char*) malloc(sizeof(char) * 2);
	var2n[0] = 'y';
	var2n[1] = 0;

	var1->setName(var1n);
	var2->setName(var2n);

	printf("(x, y, _) = (y, 5, _)\n");

	printf("RC 1: %d\n", eq->calculateFor(var1));

	printf("x quant= %f\n", var1->getQuantity());
	printf("y quant= %f\n", var2->getQuantity());
	printf("x qual = %s\n", var1->getQuality().c_str());
	printf("y qual = %s\n", var2->getQuality().c_str());

}

void test12() {

	int max = 26;

	kissms::Equationsystem *sys;
	kissms::Equation *eq[max];
	kissms::Variable *va[max];
	kissms::Constant *co;
	char *vana[max];

	sys = new kissms::Equationsystem();
	co = new kissms::Constant();
	co->setValue(23);

	for( int i = 0; i < max; i++ ) {
		eq[i] = new kissms::Equation();
		va[i] = new kissms::Variable();
		vana[i] = (char*)malloc(sizeof(char)*2);
		vana[i][0] = 97 + i;
		vana[i][1] = 0;
		va[i]->setName(vana[i]);
		eq[i]->setLeft(va[i]);
		if( i > 0 ) {
			eq[i-1]->setRight(va[i]);
		}
		if( i == max-1 ) {
			eq[i]->setRight(co);
		}
		sys->addEquation(eq[i]);
	}
	for( int i = 0; i < max; i++ ) {
		printf("%s = %s\n", eq[i]->getLeft()->getQuality().c_str(), eq[i]->getRight()->getQuality().c_str());
	}
	printf("\n");
	sys->calculateFor(va[0]);
	for( int i = 0; i < max; i++ ) {
		printf("%s = %s\n", va[i]->getName(), va[i]->getQuality().c_str());
	}
	printf("\n");
	for( int i = 0; i < max; i++ ) {
		printf("%s = %f\n", va[i]->getName(), va[i]->getQuantity());
	}

}

void test13() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Vector *vec1 = new kissms::Vector();
	kissms::Vector *vec2 = new kissms::Vector();
	kissms::Variable *var1 = new kissms::Variable();
	kissms::Variable *var2 = new kissms::Variable();
	kissms::Variable *var3 = new kissms::Variable();
	kissms::Constant *con1 = new kissms::Constant();

	eq->setArguments(vec1, vec2);
	vec1->setArgument(0, var1);
	vec1->setArgument(1, var2);
	vec1->setArgument(2, var3);
	vec2->setArgument(0, var2);
	vec2->setArgument(1, var3);
	vec2->setArgument(2, con1);
	con1->setValue(23);

	char *var1n = (char*) malloc(sizeof(char) * 2);
	var1n[0] = 'a';
	var1n[1] = 0;
	char *var2n = (char*) malloc(sizeof(char) * 2);
	var2n[0] = 'b';
	var2n[1] = 0;
	char *var3n = (char*) malloc(sizeof(char) * 2);
	var3n[0] = 'c';
	var3n[1] = 0;

	var1->setName(var1n);
	var2->setName(var2n);
	var3->setName(var3n);

	printf("(a, b, c) = (b, c, 23)\n");

	printf("RC 1: %d\n", eq->calculateFor(var1));

	printf("a quant= %f\n", var1->getQuantity());
	printf("b quant= %f\n", var2->getQuantity());
	printf("c quant= %f\n", var3->getQuantity());
	printf("a qual = %s\n", var1->getQuality().c_str());
	printf("b qual = %s\n", var2->getQuality().c_str());
	printf("c qual = %s\n", var3->getQuality().c_str());

}

void test14() {

	kissms::Equationsystem *eqsys = new kissms::Equationsystem();
	kissms::Equation *eq1 = new kissms::Equation();
	kissms::Equation *eq2 = new kissms::Equation();
	kissms::Variable *va1 = new kissms::Variable();
	kissms::Variable *va2 = new kissms::Variable();
	kissms::Constant *co1 = new kissms::Constant();
	kissms::Constant *co2 = new kissms::Constant();
	kissms::Addition *ad1 = new kissms::Addition();
	kissms::Addition *ad2 = new kissms::Addition();
	kissms::Negation *neg = new kissms::Negation();
	kissms::Multiplication *mu1 = new kissms::Multiplication();
	kissms::Multiplication *mu2 = new kissms::Multiplication();
	kissms::Reciprocal *re1 = new kissms::Reciprocal();
	kissms::Reciprocal *re2 = new kissms::Reciprocal();

	eqsys->addEquation(eq1);
	eqsys->addEquation(eq2);

	eq1->setArguments(ad1, mu1);
	ad1->setArguments(va1, neg);
	mu1->setArguments(va2, re1);
	neg->setArgument(co1);
	re1->setArgument(co2);

	eq2->setArguments(ad2, mu2);
	ad2->setArguments(va1, co1);
	mu2->setArguments(va2, re2);
	re2->setArgument(co1);

	co1->setValue(2);
	co2->setValue(4);

	char *va1n = (char*) malloc(sizeof(char) * 2);
	va1n[0] = 'x';
	va1n[1] = 0;
	char *va2n = (char*) malloc(sizeof(char) * 2);
	va2n[0] = 'y';
	va2n[1] = 0;

	va1->setName(va1n);
	va2->setName(va2n);

	printf("x + - 2 = y * 1/ 4\n");
	printf("x + 2 = y * 1/ 2\n");

	eqsys->calculateFor(va1);

	printf("= %f", va1->getQuantity());

}

void test15() {

	kissms::Equation *eq = new kissms::Equation();
	kissms::Addition *ad1 = new kissms::Addition();
	kissms::Addition *ad2 = new kissms::Addition();
	kissms::Multiplication *mu1 = new kissms::Multiplication();
	kissms::Multiplication *mu2 = new kissms::Multiplication();
	kissms::Negation *ne = new kissms::Negation();
	kissms::Variable *va = new kissms::Variable();
	kissms::Constant *co1 = new kissms::Constant();
	kissms::Constant *co2 = new kissms::Constant();

	eq->setArguments(mu1, mu2);
	mu1->setArguments(ad1, co1);
	mu2->setArguments(ad2, co2);
	ad1->setArguments(va, co1);
	ad2->setArguments(va, ne);
	ne->setArgument(co1);
	co1->setValue(2);
	co2->setValue(4);

	char *var1n = (char*) malloc(sizeof(char) * 2);
	var1n[0] = 'x';
	var1n[1] = 0;
	va->setName(var1n);

	printf("( x + 2 ) * 2 = ( x + - 2 ) * 4\n");

	eq->calculateFor(va);

	printf("x= %f\n", va->getQuantity());

}

void test16() {

	kissms::Equationsystem *sys = new kissms::Equationsystem();
	kissms::Equation *eq1 = new kissms::Equation();
	kissms::Equation *eq2 = new kissms::Equation();
	kissms::Equation *eq3 = new kissms::Equation();
	kissms::Addition *ad1a = new kissms::Addition();
	kissms::Addition *ad1b = new kissms::Addition();
	kissms::Addition *ad2a = new kissms::Addition();
	kissms::Addition *ad2b = new kissms::Addition();
	kissms::Addition *ad3a = new kissms::Addition();
	kissms::Addition *ad3b = new kissms::Addition();
	kissms::Negation *ne2a = new kissms::Negation();
	kissms::Negation *ne2b = new kissms::Negation();
	kissms::Variable *varX = new kissms::Variable();
	kissms::Variable *varY = new kissms::Variable();
	kissms::Variable *varZ = new kissms::Variable();
	kissms::Constant *co00 = new kissms::Constant();
	kissms::Constant *co12 = new kissms::Constant();

	sys->addEquation(eq1);
	eq1->setArguments(ad1a, ad1b);
	ad1a->setArguments(varX, varY);
	ad1b->setArguments(varZ, co12);


	sys->addEquation(eq2);
	eq2->setArguments(ad2a, ad2b);
	ad2a->setArguments(varX, ne2a);
	ad2b->setArguments(varZ, ne2b);
	ne2a->setArgument(varY);
	ne2b->setArgument(co12);


	sys->addEquation(eq3);
	eq3->setArguments(ad3a, co00);
	ad3a->setArguments(varX, ad3b);
	ad3b->setArguments(varY, varZ);


	char *varXn = (char*) malloc(sizeof(char) * 2);
	varXn[0] = 'x';
	varXn[1] = 0;
	varX->setName(varXn);

	char *varYn = (char*) malloc(sizeof(char) * 2);
	varYn[0] = 'y';
	varYn[1] = 0;
	varY->setName(varYn);

	char *varZn = (char*) malloc(sizeof(char) * 2);
	varZn[0] = 'z';
	varZn[1] = 0;
	varZ->setName(varZn);

	co00->setValue(0);
	co12->setValue(12);

	sys->calculateFor(varX);
	sys->calculateFor(varY);
	sys->calculateFor(varZ);

	printf("x= %f\n", varX->getQuantity());
	printf("x= %f\n", varY->getQuantity());
	printf("x= %f\n", varZ->getQuantity());


}

void test17() {

	// TODO Implement test17

}

int main(int argc, char **argv) {

	test1();
	printf("\n\n");
	test2();
	printf("\n\n");
	test3();
	printf("\n\n");
	test4();
	printf("\n\n");
	test5();
	printf("\n\n");
	test6();
	printf("\n\n");
	test7();
	printf("\n\n");
	test8();
	printf("\n\n");
	test9();
	printf("\n\n");
	test10();
	printf("\n\n");
	test11();
	printf("\n\n");
	test12();
	printf("\n\n");
	test13();
	printf("\n\n");
	test14();
	printf("\n\n");
	test15();
	printf("\n\n");
	test16();
	printf("\n\n");
	//test17();

	return 0;

}




