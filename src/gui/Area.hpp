/*
 * Area.hpp
 *
 *  Created on: Dec 2, 2013
 *      Author: kevin
 */

#ifndef AREA_HPP_
#define AREA_HPP_

#include "gui/TSingleton.cpp"
#include "gui/Frame.hpp"
#define AREA Area::Get()

class Area:public TSingleton<Area>,public Frame{
public:
	SDL_Rect* getAsRect(){
		SDL_Rect *rect = new SDL_Rect();
		rect->x=xy[0];
		rect->y=xy[1];
		rect->w=xy[2]-xy[0];
		rect->h=xy[3]-xy[1];
		return rect;
	}
};



#endif /* AREA_HPP_ */
