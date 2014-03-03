/*
 * Brush.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: kevin
 */

#include "gui/Brush.hpp"
#include "gui/Area.hpp"
#include "physic/physiccore.h"
#include "physic/solids/rigidrect.h"
#include <math.h>
#include <iostream>

#define PCAP Physiccore::Get()->getAnchorsPosition()

using std::cout;
using std::endl;

Brush::Brush(){
	color = new unsigned char[3];
	IDMethod=0;
	surfTemp= SDL_CreateRGBSurface(SDL_SWSURFACE, FRAMEWORK->getAppWidth(), FRAMEWORK->getAppHeight(), 32, SCREEN->format->Rmask, SCREEN->format->Gmask, SCREEN->format->Bmask, SCREEN->format->Amask);
	surfTemp2= SDL_CreateRGBSurface(SDL_SWSURFACE, FRAMEWORK->getAppWidth(), FRAMEWORK->getAppHeight(), 32, SCREEN->format->Rmask, SCREEN->format->Gmask, SCREEN->format->Bmask, SCREEN->format->Amask);
	//SDL_SetAlpha(surfTemp, 0, 255);
	color24=0;
	yTemp=0;
	xTemp=0;
}

//void drawCross(int x, int y){
//	hlineRGBA(SCREEN,x-4,x+4,y,0,255,0,255);
//	vlineRGBA(SCREEN,y-4,y+4,x,0,255,0,255);
//}

void Brush::getStats(){
	for(int i=0;i<TOOLS->getCount();i++){
		if(TOOLS->getButtons()[i]->getPressed()){
			setIDMethod(i);
		}
	}
}

int* Brush::checkAnchorHover(int x,int y){
	for(unsigned int i=0;i<PCAP.size();i++){
		if(abs(x-PCAP.at(i)[0])<10 && abs(y-PCAP.at(i)[1])<10){
			int f[2];
			f[0]=PCAP.at(i)[0];
			f[1]=PCAP.at(i)[1];
			return f;
		}
	}
	return NULL;
}

void Brush::paint(int x, int y, bool moved,bool initiallyPressed, bool released, bool pressed){
	if(initiallyPressed){
		xTemp=x;
		yTemp=y;
		SDL_BlitSurface(SCREEN,NULL,surfTemp,NULL);
//		printf("Pressed\n");
	}
	if(!initiallyPressed && moved){
		int *f=checkAnchorHover(x,y);
		static bool in=false;
		if(f!=NULL && in==false){
			in=true;
			circleRGBA(SCREEN,f[0],f[1],10,0,255,0,255);
			SDL_Flip(SCREEN);
		}
		if(f==NULL && in==true){
			in=false;
			SDL_BlitSurface(surfTemp,NULL,SCREEN,NULL);
		}
//		printf("Moved\n");
	}
	switch(IDMethod){
	case 2:
		if(!initiallyPressed && pressed){
			SDL_BlitSurface(surfTemp,NULL,SCREEN,NULL);
			rectangleRGBA(SCREEN,xTemp,yTemp,x,y,43,32,122,255);
			SDL_Flip(SCREEN);
		}
		if(!initiallyPressed && released){
			PHYSICCORE->addElement(*(new Rigidrect(xTemp+(x-xTemp)/2,yTemp+(y-yTemp)/2,x,y)));
			SDL_BlitSurface(SCREEN,NULL,surfTemp,NULL);

//			for(unsigned int i=0;i<PCAP.size();i++){
//				printf("%d %d\n",PCAP.at(i)[0],PCAP.at(i)[1]);
//			}
//			printf("\n");

		}
		break;
	}
}
