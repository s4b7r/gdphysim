/*
 * rigidrect.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#include "physic/physic.h"
#include "kissms/kissms.h"

Rigidrect::Rigidrect(int centerX, int centerY, int mass, int eloX, int eloY) : Solid(centerX,centerY,mass,eloX,eloY){
	anchors.push_back(*(new Anchor(eloX,eloY)));
	anchors.push_back(*(new Anchor(2*centerX-eloX,2*centerY-eloY)));
	anchors.push_back(*(new Anchor(2*centerX-eloX,eloY)));
	anchors.push_back(*(new Anchor(eloX,2*centerY-eloY)));
}


