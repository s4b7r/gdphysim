/*
 * anchor.h
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#ifndef ANCHOR_H_
#define ANCHOR_H_

//#include "kissms/kissms.h"

class Solid;

class Anchor{
private:
	bool hasForce;
	int id;
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
	void setId(int i){id=i;}
	int getId(){return id;}
	void setHasForce(bool s){hasForce = s;}
	bool getHasForce(){return hasForce;}
	void setLink(Anchor* l){link = l;}
	void setPlink(Solid* l){pLink = l;}
	Solid* getPlink(){return pLink;}
};


#endif /* ANCHOR_H_ */
