/*
 * rod.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#include "physic/solids/rod.h"
#include "physic/anchor.h"

Rod::Rod(int centerX, int centerY, int eloX, int eloY) : Solid(centerX,centerY,eloX,eloY){
	anchors.push_back(*(new Anchor(eloX,eloY)));
	anchors.push_back(*(new Anchor(2*centerX-eloX,2*centerY-eloY)));
}

