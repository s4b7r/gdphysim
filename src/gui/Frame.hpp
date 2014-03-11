/*
 * Frame.hpp
 *
 *  Created on: 20.11.2013
 *      Author: kevin
 */

#ifndef FRAME_HPP_
#define FRAME_HPP_
#include "gui/Framework.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

class Frame{
protected:
	int xy[4];
	unsigned char bgcolor[3];
public:
	Frame(int xy[4], unsigned char bgcolor[3]);
	Frame(int xy[4]);
	Frame(){};
	void build();
	bool isXy(Uint16 x, Uint16 y);
	int* getXy(){return xy;}
	unsigned char* getColor(){return bgcolor;}
	void setXy(int xy[4]);
	void setBgcolor(unsigned char bgcolor[3]);
};
#endif /* FRAME_HPP_ */
