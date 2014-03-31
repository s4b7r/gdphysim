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

	struct GlofWindow {
		int id;
		std::vector<int> subwindows;
	};

	static Glof* getGlof();

	static void deleteGlof();

	int init( int *argcp, char **argv );

	GlofModel* getModel();

	int newWindow( char *name );

	int newSubwindow( int pId, int pX, int pY, int w, int h );

	void deleteWindow( int id );

	GlofCamera* newCamera();

	void deleteCamera( GlofCamera *camera );

private:

	static Glof *myPointer;

	bool isInit;

	GlofModel *model;

	std::vector<GlofWindow> windows;

	std::vector<GlofCamera*> cameras;

	Glof();

	virtual ~Glof();

};




#endif /* GLOFC_H_ */
