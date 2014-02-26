#include "physic/physic.h"
#include "kissms/kissms.h"

using kissms::Constant;

Solid::Solid(int centerX, int centerY, int mass){
	this->mass=mass;
	fill3dVector(center,centerX,centerY,0);
}

Solid::~Solid(){						//TODO change this when Simon builds his own Vector destructor
	deleteVector(center);
	for(int i=0;i<2;i++){
		if(&forces[i]!=NULL)for(unsigned int j=0;j<forces[i].size();j++){
			deleteVector(forces[i].at(j));
			forces[i].erase(forces[i].begin()+j);
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
}
