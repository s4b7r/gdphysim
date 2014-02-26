#ifndef SOLID_H_
#define SOLID_H_

#include "kissms/kissms.h"
#include "physic/anchor.h"

using std::vector;
using kissms::Vector;

class Solid{
protected:
	int mass;
	Vector center;
	vector<Anchor> *anchors;
 	vector<Vector> forces[2]; //forces[1]: origins of forces; forces[2]: value of forces

	void deleteVector(Vector &del);

public:
	Solid(int centerX, int centerY, int mass);
	virtual ~Solid();
	static void fill3dVector(Vector &vec, int x, int y, int z);
	int getMass(){return mass;}
	Vector getCenter(){return center;}
};

#endif
