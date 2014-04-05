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
#include "physic/solids/rod.h"
#include "physic/solids/pointmass.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

#define PCAP Physiccore::Get()->getAnchorsPosition()

using std::cout;
using std::endl;

Brush::Brush(){
	color = new unsigned char[3];
	IDMethod=0;
	surfaceInitPressed= SDL_CreateRGBSurface(SDL_SWSURFACE, FRAMEWORK->getAppWidth(), FRAMEWORK->getAppHeight(), 32, SCREEN->format->Rmask, SCREEN->format->Gmask, SCREEN->format->Bmask, SCREEN->format->Amask);
	surfaceHover= SDL_CreateRGBSurface(SDL_SWSURFACE, FRAMEWORK->getAppWidth(), FRAMEWORK->getAppHeight(), 32, SCREEN->format->Rmask, SCREEN->format->Gmask, SCREEN->format->Bmask, SCREEN->format->Amask);
	surfaceArea= SDL_CreateRGBSurface(SDL_SWSURFACE, AREA->getAsRect()->w, AREA->getAsRect()->h, 32, SCREEN->format->Rmask, SCREEN->format->Gmask, SCREEN->format->Bmask, SCREEN->format->Amask);
	color24=0;
	yTemp=0;
	xTemp=0;
	SDL_BlitSurface(SCREEN,NULL,surfaceInitPressed,NULL);
	SDL_BlitSurface(SCREEN,NULL,surfaceHover,NULL);
	SDL_BlitSurface(SCREEN,AREA->getAsRect(),surfaceArea,NULL);
}

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
			int *ret = new int[2];
			ret[0]=PCAP.at(i)[0];
			ret[1]=PCAP.at(i)[1];
			return ret;
		}
	}
	return NULL;
}

void Brush::renewElements(){
	SDL_BlitSurface(surfaceArea,NULL,SCREEN,AREA->getAsRect());
	PHYSICCORE->draftElements();
	SDL_Flip(SCREEN);
}

void Brush::paint(int x, int y, bool moved, bool initiallyLeftPressed, bool released, bool pressed){
	static bool inAnchorProximity=false;
	static bool GlobalInAnchorProximity=false;
	static int GlobalAnchorCoordsInProximity[2]={0,0};
	static bool wasInitallyLeftPressed=false;

	if(initiallyLeftPressed){
		wasInitallyLeftPressed=true;
		if(inAnchorProximity)GlobalInAnchorProximity=true;
		xTemp=x;
		yTemp=y;
		if(inAnchorProximity){
			inAnchorProximity=false;
			SDL_BlitSurface(SCREEN,NULL,surfaceHover,NULL);
		}
	}

	if(moved){
		int *AnchorCoordsInProximity=checkAnchorHover(x,y);

		if(AnchorCoordsInProximity!=NULL && !inAnchorProximity){

			inAnchorProximity=true;
			SDL_BlitSurface(SCREEN,NULL,surfaceHover,NULL);
			circleRGBA(SCREEN,AnchorCoordsInProximity[0],AnchorCoordsInProximity[1],10,0,255,0,255);
			SDL_Flip(SCREEN);
			GlobalAnchorCoordsInProximity[0]=AnchorCoordsInProximity[0];
			GlobalAnchorCoordsInProximity[1]=AnchorCoordsInProximity[1];
		}
		if(AnchorCoordsInProximity==NULL && inAnchorProximity){
			inAnchorProximity=false;
			SDL_BlitSurface(surfaceHover,NULL,SCREEN,NULL);
			SDL_Flip(SCREEN);
		}
	}

	switch(IDMethod){
	case 6:		//Compute
		if(!initiallyLeftPressed && released && wasInitallyLeftPressed){
			PHYSICCORE->solve();
		}
		break;
	case 5:		//Ground
		//		if(!initiallyLeftPressed && released && wasInitallyLeftPressed){
		if(initiallyLeftPressed){
			PHYSICCORE->groundHoveredAnchors(x,y);
			GlobalInAnchorProximity=false;
			wasInitallyLeftPressed=false;
			renewElements();
		}
		break;
	case 4:		//Link
		//		if(!initiallyLeftPressed && released && wasInitallyLeftPressed){
		if(initiallyLeftPressed){
			PHYSICCORE->linkHoveredAnchors(x,y);
			GlobalInAnchorProximity=false;
			wasInitallyLeftPressed=false;
			renewElements();
		}
		break;
	case 2:		//Rigid Rectangle
		if(initiallyLeftPressed){
			SDL_BlitSurface(surfaceHover,NULL,SCREEN,NULL);
			SDL_BlitSurface(SCREEN,NULL,surfaceInitPressed,NULL);
		}
		if(!initiallyLeftPressed && pressed){
			SDL_BlitSurface(surfaceInitPressed,NULL,SCREEN,NULL);
			if(GlobalInAnchorProximity){
				rectangleRGBA(SCREEN,GlobalAnchorCoordsInProximity[0],GlobalAnchorCoordsInProximity[1],x,y,0,0,0,255);
			}else{
				rectangleRGBA(SCREEN,xTemp,yTemp,x,y,0,0,0,255);
			}
			SDL_Flip(SCREEN);
		}
		if(!initiallyLeftPressed && released && wasInitallyLeftPressed){
			if(GlobalInAnchorProximity){
				PHYSICCORE->addElement(new Rigidrect(GlobalAnchorCoordsInProximity[0]+(x-GlobalAnchorCoordsInProximity[0])/2,GlobalAnchorCoordsInProximity[1]+(y-GlobalAnchorCoordsInProximity[1])/2,GlobalAnchorCoordsInProximity[0],GlobalAnchorCoordsInProximity[1]));
			}else{
				PHYSICCORE->addElement(new Rigidrect(xTemp+(x-xTemp)/2,yTemp+(y-yTemp)/2,x,y));
			}
			GlobalInAnchorProximity=false;
			wasInitallyLeftPressed=false;
			renewElements();
		}
		break;
	case 0:		//Pointmass
		if(!initiallyLeftPressed && released && wasInitallyLeftPressed){
			if(GlobalInAnchorProximity){
				PHYSICCORE->addElement(new Pointmass(GlobalAnchorCoordsInProximity[0],GlobalAnchorCoordsInProximity[1]));
			}else{
				PHYSICCORE->addElement(new Pointmass(x,y));
			}
			GlobalInAnchorProximity=false;
			wasInitallyLeftPressed=false;
			renewElements();
		}
		break;
	case 1:		//Rigid Rod
		if(initiallyLeftPressed){
			SDL_BlitSurface(surfaceHover,NULL,SCREEN,NULL);
			SDL_BlitSurface(SCREEN,NULL,surfaceInitPressed,NULL);
		}
		if(!initiallyLeftPressed && pressed){
			SDL_BlitSurface(surfaceInitPressed,NULL,SCREEN,NULL);
			if(GlobalInAnchorProximity){
				lineRGBA(SCREEN,GlobalAnchorCoordsInProximity[0],GlobalAnchorCoordsInProximity[1],x,y,0,0,0,255);
			}else{
				lineRGBA(SCREEN,xTemp,yTemp,x,y,0,0,0,255);
			}
			SDL_Flip(SCREEN);
		}
		if(!initiallyLeftPressed && released && wasInitallyLeftPressed){
			if(GlobalInAnchorProximity){
				PHYSICCORE->addElement(new Rod(GlobalAnchorCoordsInProximity[0]+(x-GlobalAnchorCoordsInProximity[0])/2,GlobalAnchorCoordsInProximity[1]+(y-GlobalAnchorCoordsInProximity[1])/2,GlobalAnchorCoordsInProximity[0],GlobalAnchorCoordsInProximity[1]));
			}else{
				PHYSICCORE->addElement(new Rod(xTemp+(x-xTemp)/2,yTemp+(y-yTemp)/2,x,y));
			}
			GlobalInAnchorProximity=false;
			wasInitallyLeftPressed=false;
			renewElements();
		}
		break;
	case 3:		//Delete
		if(initiallyLeftPressed){
			PHYSICCORE->deleteHoveredElements(x,y);
			renewElements();
			//			printf("test\n");
			GlobalInAnchorProximity=false;
			wasInitallyLeftPressed=false;
		}
		break;
	}
}
