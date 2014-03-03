/*
 * rigidrect.h
 *
 *  Created on: Feb 27, 2014
 *      Author: kevin
 */

#ifndef RIGIDRECT_H_
#define RIGIDRECT_H_

#include "physic/solids/solid.h"

class Rigidrect : public Solid{
public:
	Rigidrect(int centerX, int centerY, int eloX, int eloY);
};

#endif /* RIGIDRECT_H_ */
