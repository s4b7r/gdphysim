/*
 * pointmass.h
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#ifndef POINTMASS_H_
#define POINTMASS_H_

#include "physic/solids/solid.h"

class Pointmass : public Solid{
public:
	Pointmass(int centerX, int centerY);
};

#endif /* POINTMASS_H_ */
