/*
 * rod.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#include "physic/physic.h"
#include "kissms/kissms.h"

Rod::Rod(int centerX, int centerY, int eloX, int eloY) : Solid(centerX, centerY, 0){
	Solid::fill3dVector(eloPoint,eloX,eloY,0);
}

