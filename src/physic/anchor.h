/*
 * anchor.h
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#ifndef ANCHOR_H_
#define ANCHOR_H_

using kissms::Vector;

class Anchor{
private:
	bool isGrounded;
	Vector origin;
	Anchor* link;
public:
	Anchor(int x, int y);
	~Anchor();
	//Anchor();

	bool getGrounded(){return isGrounded;}
	void setGrounded(bool state){isGrounded=state;}
	Vector getOrigin(){return origin;}
	Anchor* getLink(){return link;}
};


#endif /* ANCHOR_H_ */
