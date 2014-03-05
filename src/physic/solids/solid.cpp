#include "physic/solids/solid.h"
#include "gui/Area.hpp"
#include "gui/Brush.hpp"
#include "gui/Framework.hpp"
#include <iostream>

Solid::Solid(int centerX, int centerY, int eloX, int eloY){
	mass=0;

	eloPoint[0]=eloX;
	eloPoint[1]=eloY;
	eloPoint[2]=0;

	center[0]=centerX;
	center[1]=centerY;
	center[2]=0;
}

Solid::~Solid(){

}

void Solid::draft(){
for(unsigned int i=0;i<anchors.size();i++){
	if(anchors.at(i).getLink()!=NULL){
		circleRGBA(SCREEN,anchors.at(i).getOrigin()[0],anchors.at(i).getOrigin()[1],3,0,0,0,255);
	}
	if(anchors.at(i).getGrounded()){
		lineRGBA(SCREEN,anchors.at(i).getOrigin()[0]-4,anchors.at(i).getOrigin()[1]-4,anchors.at(i).getOrigin()[0]+4,anchors.at(i).getOrigin()[1]+4,0,0,0,255);
		lineRGBA(SCREEN,anchors.at(i).getOrigin()[0]-4,anchors.at(i).getOrigin()[1]+4,anchors.at(i).getOrigin()[0]+4,anchors.at(i).getOrigin()[1]-4,0,0,0,255);
	}
}
//	printf("Parentdraft\n");
}

void Solid::setAnchorGrounded(int num, bool s){
	anchors.at(num).setGrounded(s);
}

Anchor* Solid::getAnchorAddr(int num){
	return &(anchors.at(num));
}

void Solid::setMass(int m){
	mass=m;
	if(mass!=0){						//TODO testen
		forces[0].push_back(center);
		int* G= new int[3];
		G[0]=0;
		G[1]=mass*GRAVITY;
		G[2]=0;
		forces[1].push_back(G);
	}
}

int Solid::getCenter(dimension p){
	return center[p];
}

vector<Anchor> Solid::getAnchors(){
	return vector<Anchor>(anchors);
}

void Solid::setAnchorLink(int num, Anchor* l){
	anchors.at(num).setLink(l);
}

/*vector<int*> Solid::getForces(vecType v){
	return forces[v];
}*/

/*Solid::~Solid(){						//TODO change this when Simon builds his own Vector destructor
	deleteVector(eloPoint);
	deleteVector(center);
	for(int i=0;i<2;i++){
		if(&forces[i]!=NULL)for(unsigned int j=0;j<forces[i].size();j++){
			deleteVector(forces[i].at(j));
		}
	}
}

void Solid::fill3dVector(Vector &vec, int x, int y, int z){
	Constant* values[3];
	for(int i=0;i<3;i++) values[i]= (Constant*) malloc(sizeof(Constant));
	values[0]->setValue(x);
	values[1]->setValue(y);
	values[2]->setValue(z);
	vec.setArgument(0,values[0]);
	vec.setArgument(1,values[1]);
	vec.setArgument(2,values[2]);
}

void Solid::deleteVector(Vector &del){		//TODO erase this when Simon builds his own Vector destructor
	for(int i=0;i<3;i++){
		if(del.getArgument(i)!=NULL)free(del.getArgument(i));
	}
}*/
