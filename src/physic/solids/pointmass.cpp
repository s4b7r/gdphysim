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
	type=POINTMASS;
	Anchor *a=new Anchor(centerX,centerY,this);
	anchors.push_back(*a);
	a->setId(anchors.size()-1);
	int temp;
	cout << "Please enter mass for pointmass: (Kilogram) "<< endl;
	cin >> temp;
	Solid::setMass(temp);
//	Solid::setMass(45);
}

void Pointmass::draft(){
	circleRGBA(SCREEN,center[X],center[Y],15,0,0,0,255);
	Solid::draft();
}



