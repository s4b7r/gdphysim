/*
 * Brush.hpp
 *
 *  Created on: Dec 2, 2013
 *      Author: kevin
 */

#ifndef BRUSH_HPP_
#define BRUSH_HPP_

#include "gui/TSingleton.cpp"
#include "gui/Tools.hpp"
#include "gui/Area.hpp"
#include "gui/Framework.hpp"
#include <vector>

#define BRUSH Brush::Get()

class Brush:public TSingleton<Brush>{
private:
	unsigned char *color;
	int IDMethod;
	Uint32 color24;
	SDL_Surface *surfTemp;
	SDL_Surface *surfTemp2;
	Uint16 xTemp;
	Uint16 yTemp;

	int* checkAnchorHover(int x, int y);

public:
	Brush();
	void setColor(unsigned char color[3]){this->color=color;}
	void setIDMethod(int id){this->IDMethod=id;}
	void getStats();
	void paint(int x,int y, bool move, bool initiallyPressed, bool released, bool pressed);
};



#endif /* BRUSH_HPP_ */
