/*
 * anchor.h
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#ifndef ANCHOR_H_
#define ANCHOR_H_

class Solid;

class Anchor{
private:
	bool isGrounded;
	int origin[3];
	Anchor* link;
	Solid* pLink;
public:
	Anchor(int x, int y, Solid* p);

	bool getGrounded(){return isGrounded;}
	void setGrounded(bool state){isGrounded=state;}
	int* getOrigin();
	Anchor* getLink(){return link;}
	void setLink(Anchor* l){link = l;}
	void setPlink(Solid* l){pLink = l;}
};


#endif /* ANCHOR_H_ */
