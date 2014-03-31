/*
 * camera.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef CAMERA_H_
#define CAMERA_H_

class GlofCamera {

public:

	GlofCamera();
	virtual ~GlofCamera();

	void bindWindow( int windowId );

	void removeBind( int windowId );

	void render();

private:

	std::vector<int> windowBinds;

};



#endif /* CAMERA_H_ */
