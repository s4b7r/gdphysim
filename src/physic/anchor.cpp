/*
 * anchor.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#include "physic/physic.h"
#include "kissms/kissms.h"

Anchor::Anchor(int x, int y){
	isGrounded=false;
	Solid::fill3dVector(origin,x,y,0);
	link=NULL;
}


