/*
 * Frame.cpp
 *
 *  Created on: 20.11.2013
 *      Author: kevin
 */
#include "gui/Frame.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

Frame::Frame(int xy[4], unsigned char bgcolor[3]){
	for(int i=0;i<=3;i++){
		this->xy[i]=xy[i];
	}
	for(int i=0;i<=2;i++){
		this->bgcolor[i]=bgcolor[i];
	}
}

Frame::Frame(int xy[4]){
	for(int i=0;i<=3;i++){
		this->xy[i]=xy[i];
	}
	this->bgcolor[0]=233;
	this->bgcolor[1]=230;
	this->bgcolor[2]=222;
}

bool Frame::isXy(Uint16 x, Uint16 y){
	if(xy[0]<=x && xy[1]<=y && xy[2]>=x && xy[3]>=y){
		return true;
	}else{
		return false;
	}
}

void Frame::setXy(int xy[4]){
	for(int i=0;i<4;i++){
		this->xy[i]=xy[i];
	}
}

void Frame::setBgcolor(unsigned char bgcolor[3]){
	for(int i=0;i<3;i++){
		this->bgcolor[i]=bgcolor[i];
	}
}

void Frame::build(){
	boxRGBA(SCREEN,xy[0],xy[1],xy[2],xy[3],bgcolor[0],bgcolor[1],bgcolor[2],255);
	SDL_UpdateRect(SCREEN,xy[0],xy[1],xy[2]-xy[0],xy[3]-xy[1]);
	//SDL_Flip(SCREEN);
}



