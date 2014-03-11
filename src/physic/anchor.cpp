/*
 * anchor.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: kevin
 */

#include "physic/anchor.h"
#include <iostream>
//#include <stdio.h>

Anchor::Anchor(int x, int y,Solid* p){
//	printf("%d\n", x);
	isGrounded=false;
	origin[0]=x;
	origin[1]=y;
	origin[2]=0;
	link=NULL;
	pLink=p;
	hasForce=false;
	id=-1;
}

int* Anchor::getOrigin(){
	int *f=new int[3];
	for(int i=0;i<3;i++){
		f[i]=origin[i];
	}
	return f;
}






