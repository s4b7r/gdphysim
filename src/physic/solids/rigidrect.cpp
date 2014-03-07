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

Rigidrect::Rigidrect(int centerX, int centerY, int eloX, int eloY) : Solid(centerX,centerY,eloX,eloY){
//	printf("%d\n", eloX);
	anchors.push_back(*(new Anchor(eloX,eloY,this)));
	anchors.push_back(*(new Anchor(2*centerX-eloX,2*centerY-eloY,this)));
	anchors.push_back(*(new Anchor(2*centerX-eloX,eloY,this)));
	anchors.push_back(*(new Anchor(eloX,2*centerY-eloY,this)));
}

void Rigidrect::draft(){
	Solid::draft();
	rectangleRGBA(SCREEN,2*center[X]-eloPoint[X],2*center[Y]-eloPoint[Y],eloPoint[X],eloPoint[Y],0,0,0,255);
//	printf("childdraft\n");
}
