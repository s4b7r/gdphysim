/*
 * rod.h
 *
 *  Created on: Feb 22, 2014
 *      Author: kevin
 */

#ifndef ROD_H_
#define ROD_H_

#include "physic/solids/solid.h"

class Rod : public Solid{
public:
	Rod(int centerX, int centerY, int eloX, int eloY);
	void setMass(){;}
	void draft();
};

#endif /* ROD_H_ */
