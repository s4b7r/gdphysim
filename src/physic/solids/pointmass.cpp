/*
 * pointmass.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#include "physic/physic.h"
#include "kissms/kissms.h"

Pointmass::Pointmass(int centerX, int centerY, int mass) : Solid(centerX,centerY,mass,centerX,centerY){
	anchors.push_back(*(new Anchor(centerX,centerY)));
}



