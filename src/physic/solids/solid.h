#ifndef SOLID_H_
#define SOLID_H_

#define GRAVITY 9.81
#define PI 3.1415926

#include <vector>
#include "physic/anchor.h"
#include "stdio.h"

using std::vector;

enum vecType {fOrigin=0,fValue=1};
enum dimension {X=0,Y=1,Z=2};

class Solid{
protected:
	int mass;
	int center[3];
	int eloPoint[3];
	vector<Anchor> anchors;
 	vector<int*> forces[2]; //forces[1]: origins of forces; forces[2]: value of forces

public:
	Solid(int centerX, int centerY, int eloX, int eloY);
	virtual ~Solid();
	virtual void draft();

	/*static void deleteVector(Vector &del);
	static void fill3dVector(Vector &vec, int x, int y, int z);*/
	void setMass(int m);
	int getMass(){return mass;}
	int getCenter(dimension p);
	vector<Anchor> getAnchors();
	void setAnchorLink(int num, Anchor* l);
	void setAnchorGrounded(int num, bool s);
	Anchor* getAnchorAddr(int num);
	void drawVector(int rx, int ry, double x, double y, int r, int g, int b);
	//vector<int*> getForces(vecType v);
};

#endif
