/*
 * anchor.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#include "physic/physic.h"
#include "kissms/kissms.h"

using std::cout;
using std::endl;

Anchor::Anchor(int x, int y){
	isGrounded=false;
	Solid::fill3dVector(origin,x,y,0);
	link=NULL;
}

Anchor::~Anchor(){
	Solid::deleteVector(origin);
	//cout << "Anchor destroyed" << endl;
}


