/*
 * anchor.h
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#ifndef ANCHOR_H_
#define ANCHOR_H_

class Anchor{
private:
	bool isGrounded;
	int origin[3];
	Anchor* link;
public:
	Anchor(int x, int y);

	bool getGrounded(){return isGrounded;}
	void setGrounded(bool state){isGrounded=state;}
	int* getOrigin();
	Anchor* getLink(){return link;}
};


#endif /* ANCHOR_H_ */
