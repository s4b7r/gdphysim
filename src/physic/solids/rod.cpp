/*
 * rod.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#include "physic/solids/rod.h"
#include "physic/anchor.h"
#include "gui/Framework.hpp"

Rod::Rod(int centerX, int centerY, int eloX, int eloY) : Solid(centerX,centerY,eloX,eloY){
	type=ROD;
	Anchor *a=new Anchor(eloX,eloY,this);
	anchors.push_back(*a);
	a->setId(anchors.size()-1);
	a=new Anchor(2*centerX-eloX,2*centerY-eloY,this);
	anchors.push_back(*a);
	a->setId(anchors.size()-1);
	variance=3;
	Solid::setMass(0);
}
void Rod::draft(){
	lineRGBA(SCREEN,2*center[X]-eloPoint[X],2*center[Y]-eloPoint[Y],eloPoint[X],eloPoint[Y],0,0,0,255);
	Solid::draft();
}
