/*
 * vectorproduct.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Vectorproduct::Vectorproduct() {
}

Vectorproduct::~Vectorproduct() {
}

ResultCode Vectorproduct::reformFor(Variable* variable,
		Component** newSide, Component** otherSide) {

	return ImpossibleState;

}

ResultCode Vectorproduct::calculate() {

	return ImpossibleState;

}

Vector* Vectorproduct::getVector() {

	Vector *result = new Vector();
	Addition *add[3];
	Multiplication *mu[3][2];
	int index[2];
	index[0] = 2;
	index[1] = 3;

	for( int i = 0; i < 3; i++ ) {
		add[i] = new Addition();
		for( int j = 0; j < 2; j++ ) {
			mu[i][j] = new Multiplication();
			mu[i][j]->setLeft(((Vector*)argumentLeft)->getArgument(index[j]));
			mu[i][j]->setRight(((Vector*)argumentRight)->getArgument(index[1-j]));
		}
		add[i]->setArguments(mu[i][0], mu[i][1]);
		result->setArgument(i, add[i]);
		index[0] = index[0] == 3 ? 1 : index[0]+1;
		index[1] = index[1] == 3 ? 1 : index[1]+1;
	}

	return result;

}

}


