#include "physic/solid.h"

using namespace kissms;

Solid::Solid(int centerX, int centerY, int mass){
	this->mass=mass;
	Constant values[2];
	values[0].setValue(centerX);
	values[1].setValue(centerY);
	center.setArgument(0, &values[0]);
	center.setArgument(1, &values[1]);
}

Solid::~Solid(){

}

void Solid::fill3dVector(Vector &vec, int x, int y, int z){
	Constant values[3];
	values[0].setValue(x);
	values[1].setValue(y);
	values[2].setValue(z);
	vec.setArgument(0,&values[0]);
	vec.setArgument(1,&values[1]);
	vec.setArgument(2,&values[2]);
}

void Solid::deleteVector(Vector &del){
	for(int i=0;i<3;i++)delete(del.getArgument(i));
	delete(&del);
}
