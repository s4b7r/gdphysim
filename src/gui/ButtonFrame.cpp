/*
 * ButtonFrame.cpp
 *
 *  Created on: 27.11.2013
 *      Author: kstreser
 */

#include "gui/ButtonFrame.hpp"
#define xy Frame::getXy()

ButtonFrame::ButtonFrame(int count) : Frame(){
	this->count=count;
	buttons = new Button*[count];
	buttonCoords= new int*[count];
	for(int i=0;i<count;i++){
		buttonCoords[i]= new int[4];
	}

	buttonSize = 50;
}

void ButtonFrame::buildButtons(String filenames[]){
	for(int i=0;i<count;i++){
		buttons[i] = new Button(buttonCoords[i],filenames[i],this->bgcolor);
	}
}

void ButtonFrame::buildButtons(unsigned char bgcolor[][3]){
	for(int i=0;i<count;i++){
		buttons[i] = new Button(buttonCoords[i],bgcolor[i],this->bgcolor);
	}
}

void ButtonFrame::computeButtonCoords(){
	int B=(int)xy[2]-xy[0];
	int H=(int)xy[3]-xy[1];
	/*printf("%d\n",B);
	printf("%d\n",H);*/

	int buttonsPerRow=(int)(((2*B)/(3*buttonSize))-1/3);
	int buttonsPerCol=(int)(((2*H)/(3*buttonSize))-1/3);

	int x=(int)(B/(buttonsPerRow+1));
	int y=(int)(H/(buttonsPerCol+1));

	int c=count;
	for(int j=0;c!=0;j++){
		for(int i=0;i<buttonsPerRow && c!=0;i++){
			buttonCoords[c-1][0]=(int)(xy[0]+(x*(i+1)-(buttonSize-1)/2));
			buttonCoords[c-1][1]=(int)(xy[1]+(y*(j+1)-(buttonSize-1)/2));
			buttonCoords[c-1][2]=buttonCoords[c-1][0]+(buttonSize-1);
			buttonCoords[c-1][3]=buttonCoords[c-1][1]+(buttonSize-1);
			c--;
		}
	}
}

