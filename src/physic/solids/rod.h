/*
 * rod.h
 *
 *  Created on: Feb 22, 2014
 *      Author: kevin
 */

#ifndef ROD_H_
#define ROD_H_

class Rod : public Solid{

private:
	Vector eloPoint;

public:
	Rod(int centerX, int centerY, int eloX, int eloY);
};

#endif /* ROD_H_ */
