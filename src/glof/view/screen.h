/*
 * screen.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef SCREEN_H_
#define SCREEN_H_


class GlofScreen {

public:

	GlofScreen();
	virtual ~GlofScreen();

	GlofViewport* newViewport();

private:

	std::vector<GlofViewport*> viewports;

};




#endif /* SCREEN_H_ */
