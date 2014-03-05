/*
 * pointmass.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#include "physic/solids/pointmass.h"
#include "physic/anchor.h"
#include "gui/Framework.hpp"

Pointmass::Pointmass(int centerX, int centerY) : Solid(centerX,centerY,centerX,centerY){
	anchors.push_back(*(new Anchor(centerX,centerY,this)));
}

void Pointmass::draft(){
	Solid::draft();
	circleRGBA(SCREEN,center[X],center[Y],15,0,0,0,255);
}



