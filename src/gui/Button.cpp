/*
 * button.cpp
 *
 *  Created on: 30.10.2013
 *      Author: kevin
 */

#include "gui/Button.hpp"

Button::Button(int xy[4],string filename,unsigned char bbcolor[3]) : Frame(xy){
	this->filename=filename;
	isColored=false;
	for(int i=0;i<3;i++){
		this->bbcolor[i]=bbcolor[i];
	}
	setPressed(false);
}

Button::Button(int xy[4], unsigned char bgcolor[3],unsigned char bbcolor[3]) : Frame(xy,bgcolor){
	isColored=true;
	for(int i=0;i<3;i++){
		this->bbcolor[i]=bbcolor[i];
	}
	setPressed(false);
}

void Button::build(bool pressed){

	SDL_Rect drect;

	if(!pressed){
		drect.x = Frame::xy[0]+2;
		drect.y = Frame::xy[1];
		drect.w = Frame::xy[2]-Frame::xy[0]-2;
		drect.h= Frame::xy[3]-Frame::xy[1]-2;
		boxRGBA(SCREEN,Frame::xy[0],Frame::xy[1]+2,Frame::xy[2]-2,Frame::xy[3],0,0,0,255);
	}else{
		drect.x = Frame::xy[0];
		drect.y = Frame::xy[1]+2;
		drect.w = Frame::xy[2]-Frame::xy[0]-2;
		drect.h= Frame::xy[3]-Frame::xy[1]-2;
		boxRGBA(SCREEN,Frame::xy[0],Frame::xy[1],Frame::xy[2],Frame::xy[3],bbcolor[0],bbcolor[1],bbcolor[2],255);
		//printf("%d\n",bbcolor[0]);
	}
	if(isColored){
		boxRGBA(SCREEN,drect.x,drect.y,drect.x+drect.w,drect.y+drect.h,Frame::bgcolor[0],bgcolor[1],bgcolor[2],255);
	}else{
		SDL_Surface* image = SDL_LoadBMP(filename.c_str());
		SDL_BlitSurface(image, NULL, SCREEN, &drect);
	}
	SDL_UpdateRect(SCREEN,Frame::xy[0],Frame::xy[1],Frame::xy[2]-Frame::xy[0]+1,Frame::xy[3]-Frame::xy[1]+1);
	//SDL_Flip(SCREEN);
}

void Button::setPressed(bool pressed){
	this->pressed = pressed;
	build(this->pressed);
}

