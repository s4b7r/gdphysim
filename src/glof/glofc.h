/*
 * glofc.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef GLOFC_H_
#define GLOFC_H_

class Glof {

public:
	static Glof* getGlof();

	static void deleteGlof();

	int init( int *argcp, char **argv );

	GlofModel* getModel();

	GlofScreen* newScreen();


private:

	static Glof *myPointer;

	bool isInit;

	GlofModel* model;

	std::vector<GlofScreen> screens;

	Glof();

	virtual ~Glof();

};




#endif /* GLOFC_H_ */
