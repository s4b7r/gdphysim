/*
 * Framework.hpp
 *
 *  Created on: 14.11.2013
 *      Author: kevin
 */
#ifndef FRAMEWORK_HPP_
#define FRAMEWORK_HPP_
#include "gui/TSingleton.cpp"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#define FRAMEWORK Framework::Get()
#define SCREEN Framework::Get()->getScreen()
#define APPWIDTH Framework::Get()->getAppWidth()
#define APPHEIGHT Framework::Get()->getAppHeight()

class Framework : public TSingleton<Framework>{
public:
	bool init(int appWidth, int appHeight);
	SDL_Surface* getScreen(){return screen;}
	void flip(){SDL_Flip(screen);}
	void quit(){SDL_Quit();}
	int getAppWidth(){return appWidth;}
	int getAppHeight(){return appHeight;}
	void eventProc();

private:
	SDL_Surface *screen;
	int appWidth;
	int appHeight;
	template <class T> void buttonPressing(T *b, SDL_Event event);
};
#endif /* FRAMEWORK_HPP_ */
