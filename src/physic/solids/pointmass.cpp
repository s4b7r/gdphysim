/*
 * pointmass.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#include "physic/solids/pointmass.h"
#include "physic/anchor.h"
#include "gui/Framework.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

Pointmass::Pointmass(int centerX, int centerY) : Solid(centerX,centerY,centerX,centerY){
	anchors.push_back(*(new Anchor(centerX,centerY,this)));
	int temp;
	cout << "Please enter mass for pointmass: (Kilogram) "<< endl;
	cin >> temp;
	Solid::setMass(temp);
}

void Pointmass::draft(){
	Solid::draft();
	circleRGBA(SCREEN,center[X],center[Y],15,0,0,0,255);
}



