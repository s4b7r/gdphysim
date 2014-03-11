#ifndef SOLID_H_
#define SOLID_H_

#define GRAVITY 9.81
#define PI 3.1415926

#include <vector>
#include "physic/anchor.h"
#include "stdio.h"
#include <string>

using std::vector;
using std::string;

enum vecType {fOrigin=0,fValue=1};
enum dimension {X=0,Y=1,Z=2};
enum solidType {RAW=0,ROD=1,POINTMASS=2,RIGIDRECT=3};

class Solid{
protected:
	int id;
	solidType type;
	int mass;
	int center[3];
	int eloPoint[3];
	vector<Anchor> anchors;
 	vector<int*> forces[2]; //forces[0]: origins of forces; forces[1]: value of forces

public:
	Solid(int centerX, int centerY, int eloX, int eloY);
	virtual ~Solid();
	virtual void draft();

	/*static void deleteVector(Vector &del);
	static void fill3dVector(Vector &vec, int x, int y, int z);*/
	void setMass(int m);
	int getMass(){return mass;}
	void setId(int i){id=i;}
	int getId(){return id;}
	solidType getType(){return type;}
	int getCenter(dimension p);
	void addForces(vecType i,int x, int y, int z);
	int getForces(vecType i, int num, dimension p);
	vector<Anchor> getAnchors();
	void setAnchorLink(int num, Anchor* l);
	void setAnchorGrounded(int num, bool s);
	Anchor* getAnchorAddr(int num);
	void drawVector(int rx, int ry, double x, double y, int r, int g, int b);
	//vector<int*> getForces(vecType v);
};

#endif
