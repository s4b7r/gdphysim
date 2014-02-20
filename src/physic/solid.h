#include "kissms/kissms.h"

using namespace kissms;

class Solid{
protected:
	int mass;
	Vector center;
	vector<Vector> forces[2];
	
	void deleteVector(Vector &del);
	
public:
	Solid(int centerX, int centerY, int mass);
	virtual ~Solid();
	void fill3dVector(Vector &vec, int x, int y, int z);
}
