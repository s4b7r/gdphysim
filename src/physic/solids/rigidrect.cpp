/*
 * rigidrect.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#include "physic/solids/rigidrect.h"
#include "physic/anchor.h"
//#include <stdio.h>

Rigidrect::Rigidrect(int centerX, int centerY, int eloX, int eloY) : Solid(centerX,centerY,eloX,eloY){
//	printf("%d\n", eloX);
	anchors.push_back(*(new Anchor(eloX,eloY)));
	anchors.push_back(*(new Anchor(2*centerX-eloX,2*centerY-eloY)));
	anchors.push_back(*(new Anchor(2*centerX-eloX,eloY)));
	anchors.push_back(*(new Anchor(eloX,2*centerY-eloY)));
}


