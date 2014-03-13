/*
 * Button.hpp
 *
 *  Created on: 30.10.2013
 *      Author: kevin
 */
#ifndef BUTTON_HPP_
#define BUTTON_HPP_
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "gui/Frame.hpp"

using std::string;

class Button : public Frame{

public:
//	Button(){};
	Button(int xy[4],string filename,unsigned char bbcolor[3]);
	Button(int xy[4], unsigned char bgcolor[3],unsigned char bbcolor[3]);
	bool getPressed(){return pressed;}
	void setPressed(bool pressed);
	void build(bool pressed);

private:
	bool pressed;
	bool isColored;
	string filename;
	unsigned char bbcolor[3];
};


#endif /* BUTTON_HPP_ */
