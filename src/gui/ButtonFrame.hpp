/*
 * ButtonFrame.hpp
 *
 *  Created on: 27.11.2013
 *      Author: kstreser
 */

#ifndef BUTTONFRAME_HPP_
#define BUTTONFRAME_HPP_

#include "gui/Button.hpp"


class ButtonFrame : public Frame{
private:
	Button **buttons;
	int count;
	int **buttonCoords;
	int buttonSize;

public:
	ButtonFrame(int count);
	Button** getButtons(){return buttons;}
	int getCount(){return count;}
	void computeButtonCoords();
	void buildButtons(String filenames[]);
	void buildButtons(unsigned char bgcolor[][3]);
};

#endif /* BUTTONFRAME_HPP_ */
