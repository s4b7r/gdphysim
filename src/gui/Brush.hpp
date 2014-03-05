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
	SDL_Surface *surfaceInitPressed;
	SDL_Surface *surfaceHover;
	SDL_Surface *surfaceArea;
	Uint16 xTemp;
	Uint16 yTemp;

	void renewElements();
	int* checkAnchorHover(int x, int y);

public:
	Brush();
	void setColor(unsigned char color[3]){this->color=color;}
	void setIDMethod(int id){this->IDMethod=id;}
	void getStats();
	void paint(int x,int y, bool move, bool initiallyLeftPressed, bool released, bool pressed);
	SDL_Surface* getSurfHover(){return surfaceHover;}
	SDL_Surface* getSurfInitPressed(){return surfaceInitPressed;}
	SDL_Surface* getSurfArea(){return surfaceArea;}
};



#endif /* BRUSH_HPP_ */
