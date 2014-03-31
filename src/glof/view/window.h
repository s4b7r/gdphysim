/*
 * window.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef WINDOW_H_
#define WINDOW_H_


class GlofWindow {

public:

	GlofWindow();
	virtual ~GlofWindow();

	void setName( char *name );

	void setPosition( int x, int y );

	void setSize( int w, int h );

	int init();

	GlofWindow* newSubwindow();

	void setParent( GlofWindow *parent );

	int getId();

private:

	int glutId;

	bool isInit;

	char *name;

	int x;
	int y;

	int w;
	int h;

	GlofWindow *parent;

	std::vector<GlofWindow*> windows;

};


#endif /* WINDOW_H_ */
