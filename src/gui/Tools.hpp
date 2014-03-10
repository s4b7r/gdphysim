/*
 * Tools.hpp
 *
 *  Created on: Nov 25, 2013
 *      Author: kevin
 */

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include "gui/TSingleton.cpp"
#include "gui/Button.hpp"
#include "gui/ButtonFrame.hpp"
#define TOOLS Tools::Get()
#define COUNTT 6

class Tools : public TSingleton<Tools>, public ButtonFrame{
public:
	Tools():ButtonFrame(COUNTT){}
	void build(){
		Frame::build();
		computeButtonCoords();
		string filenames[]={"res/pointmass.bmp","res/rod.bmp","res/rect.bmp","res/delete.bmp","res/link.bmp","res/ground.bmp"};
		ButtonFrame::buildButtons(filenames);
	}
};

#endif /* TOOLS_HPP_ */
