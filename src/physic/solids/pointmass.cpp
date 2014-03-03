/*
 * pointmass.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#include "physic/solids/pointmass.h"
#include "physic/anchor.h"

Pointmass::Pointmass(int centerX, int centerY) : Solid(centerX,centerY,centerX,centerY){
	anchors.push_back(*(new Anchor(centerX,centerY)));
}



