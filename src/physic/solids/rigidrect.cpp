/*
 * rigidrect.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#include "physic/solids/rigidrect.h"
#include "physic/anchor.h"
#include "gui/Framework.hpp"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

Rigidrect::Rigidrect(int centerX, int centerY, int eloX, int eloY) : Solid(centerX,centerY,eloX,eloY){
	//	printf("%d\n", eloX);
	type=RIGIDRECT;
	Anchor *a=new Anchor(eloX,eloY,this);
	anchors.push_back(*a);
	a->setId(anchors.size()-1);
	a=new Anchor(2*centerX-eloX,2*centerY-eloY,this);
	anchors.push_back(*a);
	a->setId(anchors.size()-1);
	a=new Anchor(2*centerX-eloX,eloY,this);
	anchors.push_back(*a);
	a->setId(anchors.size()-1);
	a=new Anchor(eloX,2*centerY-eloY,this);
	anchors.push_back(*a);
	a->setId(anchors.size()-1);
//	int temp;
//	cout << "Please enter mass for rectangle: (Kilogram) "<< endl;
//	cin >> temp;
//	Solid::setMass(temp);
	Solid::setMass(45);
}

void Rigidrect::draft(){
	rectangleRGBA(SCREEN,2*center[X]-eloPoint[X],2*center[Y]-eloPoint[Y],eloPoint[X],eloPoint[Y],0,0,0,255);
	//	printf("childdraft\n");
	Solid::draft();
}

