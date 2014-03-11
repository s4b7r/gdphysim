/*
 * Framework.cpp
 *
 *  Created on: 15.11.2013
 *      Author: kevin
 */

#include "gui/Framework.hpp"
#include "gui/Tools.hpp"
#include "gui/Area.hpp"
#include "gui/Brush.hpp"
#include <iostream>

using namespace std;

bool Framework::init(int appWidth, int appHeight){
	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		cout << "Fehler beim Initialisieren der SDL" << endl;
		cout << "Fehlermeldung: "<< SDL_GetError() << endl;
		quit();
		return false;
	}else{
		screen = SDL_SetVideoMode(appWidth,appHeight,32,SDL_SWSURFACE);
		//SDL_SetAlpha(screen, 0, 255);

		int boxesWidth = appWidth/5;
		int boxesHeight = appHeight;

		int crdsTools[]={0,0,boxesWidth,boxesHeight};
		int crdsArea[]={boxesWidth+1,0,appWidth-1,appHeight};
		//int crdsColor[]={0,appHeight-ColorsHeight,boxesWidth,appHeight};

		unsigned char stdBack[]={233,230,222};
		unsigned char white[]={255,255,255};
		TOOLS->setXy(crdsTools);
		TOOLS->setBgcolor(stdBack);
		TOOLS->build();
		AREA->setXy(crdsArea);
		AREA->setBgcolor(white);
		AREA->build();

		FRAMEWORK->flip();
		this->appHeight=appHeight;
		this->appWidth=appWidth;
		return true;
	}
}

template <class T> void Framework::buttonPressing(T *bframe, SDL_Event event){
	if(bframe->isXy(event.button.x,event.button.y)){
		//printf("Tools\n");
		for(int i=0;i<bframe->getCount();i++){
			if(bframe->getButtons()[i]->isXy(event.button.x,event.button.y)){
				bframe->getButtons()[i]->setPressed(true);			// set the pressed button pressed
				for(int j=0;j<bframe->getCount();j++){
					if(j!=i){
						bframe->getButtons()[j]->setPressed(false); // set all other buttons in bfame unpressed
					}
				}
				break;
			}
		}
		BRUSH->getStats();
	}
}

void Framework::eventProc(){
	bool run=true;
	SDL_Event event;

	while(run){
		while(SDL_PollEvent(&event)){
			//printf("%d\n",event.type);
//			printf("%d\n",event.motion.state);
			switch(event.type){

			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button==SDL_BUTTON_LEFT){
					buttonPressing(TOOLS,event);
					if(TOOLS->isXy(event.motion.x,event.motion.y)){
						SDL_BlitSurface(SCREEN,NULL,BRUSH->getSurfHover(),NULL);
						SDL_BlitSurface(SCREEN,NULL,BRUSH->getSurfInitPressed(),NULL);
					}
					if(AREA->isXy(event.motion.x,event.motion.y)){
						BRUSH->paint(event.motion.x,event.motion.y,false,true,false,true);
					}
				}
				break;
			case SDL_MOUSEMOTION:
				if(event.motion.state==SDL_PRESSED && AREA->isXy(event.motion.x,event.motion.y)){
					BRUSH->paint(event.motion.x,event.motion.y,true,false,false,true);
				}
				if(event.motion.state==0 && AREA->isXy(event.motion.x,event.motion.y)){
					BRUSH->paint(event.motion.x,event.motion.y,true,false,false,false);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(AREA->isXy(event.motion.x,event.motion.y)){
					BRUSH->paint(event.motion.x,event.motion.y,false,false,true,false);
					//cout << "MButton released" << endl;
				}
				break;

			case SDL_QUIT:
				run=false;
				break;
			}
		}
	}
}

