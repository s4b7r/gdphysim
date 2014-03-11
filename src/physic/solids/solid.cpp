#include "physic/solids/solid.h"
#include "gui/Area.hpp"
#include "gui/Brush.hpp"
#include "gui/Framework.hpp"
#include <iostream>
#include <stdlib.h>

Solid::Solid(int centerX, int centerY, int eloX, int eloY){
	mass=0;
	type=RAW;

	eloPoint[0]=eloX;
	eloPoint[1]=eloY;
	eloPoint[2]=0;

	center[0]=centerX;
	center[1]=centerY;
	center[2]=0;

	id=-1;
}

Solid::~Solid(){

}

void Solid::clearSolid(){
	forces[fOrigin].clear();
	forces[fValue].clear();
	setMass(mass);
}

void Solid::drawVector(int rx, int ry, double x, double y, int r, int g, int b){
	if(x==0 && y==0)return;

	int a=8;	//Arrow blade length
	string file="res/numbers.bmp";
	SDL_Surface* numbersImage=SDL_LoadBMP(file.c_str());
	vector<int> vec;
	SDL_Rect numberRect;
	SDL_Rect drect;

	numberRect.h=9;
	numberRect.w=6;
	drect.h=numberRect.h;
	drect.w=numberRect.w;

	int abs=sqrt((x*x)+(y*y));
	if(abs>250){
		y=y/abs*100;
		x=x/abs*100;
	}else{
		y=y*0.4;
		x=x*0.4;
	}

	drect.x=1+rx+x/2;
	drect.y=1+ry+y/2;

	lineRGBA(SCREEN,rx,ry,rx+x,ry+y,r,g,b,255);
	double alpha;
	alpha=atan(y/x);
	if(x<0){
		lineRGBA(SCREEN,rx+x,ry+y,rx+x+a*-cos(alpha+0.75*PI),ry+y+a*-sin(alpha+0.75*PI),r,g,b,255);
		lineRGBA(SCREEN,rx+x,ry+y,rx+x+a*-cos(alpha+1.25*PI),ry+y+a*-sin(alpha+1.25*PI),r,g,b,255);
	}else{
		lineRGBA(SCREEN,rx+x,ry+y,rx+x+a*cos(alpha+0.75*PI),ry+y+a*sin(alpha+0.75*PI),r,g,b,255);
		lineRGBA(SCREEN,rx+x,ry+y,rx+x+a*cos(alpha+1.25*PI),ry+y+a*sin(alpha+1.25*PI),r,g,b,255);
	}


	for(int j=abs;j>0;){
		vec.insert(vec.begin(),j%10);
		j/=10;
	}
	for(unsigned int i=0;i<vec.size();i++){
		switch(vec.at(i)){
		case 0:
			numberRect.x=147;
			numberRect.y=0;
			break;
		case 1:
			numberRect.x=3;
			numberRect.y=0;
			break;
		case 2:
			numberRect.x=19;
			numberRect.y=0;
			break;
		case 3:
			numberRect.x=35;
			numberRect.y=0;
			break;
		case 4:
			numberRect.x=51;
			numberRect.y=0;
			break;
		case 5:
			numberRect.x=67;
			numberRect.y=0;
			break;
		case 6:
			numberRect.x=83;
			numberRect.y=0;
			break;
		case 7:
			numberRect.x=99;
			numberRect.y=0;
			break;
		case 8:
			numberRect.x=115;
			numberRect.y=0;
			break;
		case 9:
			numberRect.x=131;
			numberRect.y=0;
			break;
		}
		SDL_BlitSurface(numbersImage, &numberRect, SCREEN, &drect);
		drect.x=drect.x+6;
	}
//	printf("\n");
	SDL_Flip(SCREEN);
}

void Solid::draft(){
	for(unsigned int i=0;i<forces[0].size();i++){
		drawVector(forces[0].at(i)[X],forces[0].at(i)[Y],forces[1].at(i)[X],forces[1].at(i)[Y],255,0,0);
	}

//	for(int j=-1;j<2;j++){
//		for(int k=-1;k<2;k++){
//			drawVector(500,400,j*548,k*387,0,0,0);
//		}
//	}

	for(unsigned int i=0;i<anchors.size();i++){
		if(anchors.at(i).getLink()!=NULL){
			circleRGBA(SCREEN,anchors.at(i).getOrigin()[0],anchors.at(i).getOrigin()[1],3,0,0,0,255);
		}
		if(anchors.at(i).getGrounded()){
			lineRGBA(SCREEN,anchors.at(i).getOrigin()[0]-4,anchors.at(i).getOrigin()[1]-4,anchors.at(i).getOrigin()[0]+4,anchors.at(i).getOrigin()[1]+4,0,0,0,255);
			lineRGBA(SCREEN,anchors.at(i).getOrigin()[0]-4,anchors.at(i).getOrigin()[1]+4,anchors.at(i).getOrigin()[0]+4,anchors.at(i).getOrigin()[1]-4,0,0,0,255);
		}
	}
	//	printf("Parentdraft\n");
}

void Solid::setAnchorGrounded(int num, bool s){
	anchors.at(num).setGrounded(s);
}

Anchor* Solid::getAnchorAddr(int num){
	return &(anchors.at(num));
}

void Solid::setMass(int m){
	mass=m;
	if(mass!=0){
		forces[0].push_back(center);
		int* G= new int[3];
		G[0]=0;
		G[1]=mass*GRAVITY;
		G[2]=0;
		forces[1].push_back(G);
	}
}

int Solid::getForces(vecType i, int num, dimension p){
	return forces[i].at(num)[p];
}

void Solid::addForces(vecType i,int x, int y, int z){
	int *force=new int[3];
	force[0]=x;
	force[1]=y;
	force[2]=z;
	forces[i].push_back(force);
}

int Solid::getCenter(dimension p){
	return center[p];
}

vector<Anchor> Solid::getAnchors(){
	return vector<Anchor>(anchors);
}

//vector<Anchor> Solid::getAnchors(){
//	return anchors;
//}

void Solid::setAnchorLink(int num, Anchor* l){
	anchors.at(num).setLink(l);
}

/*vector<int*> Solid::getForces(vecType v){
	return forces[v];
}*/

/*Solid::~Solid(){						//TODO change this when Simon builds his own Vector destructor
	deleteVector(eloPoint);
	deleteVector(center);
	for(int i=0;i<2;i++){
		if(&forces[i]!=NULL)for(unsigned int j=0;j<forces[i].size();j++){
			deleteVector(forces[i].at(j));
		}
	}
}

void Solid::fill3dVector(Vector &vec, int x, int y, int z){
	Constant* values[3];
	for(int i=0;i<3;i++) values[i]= (Constant*) malloc(sizeof(Constant));
	values[0]->setValue(x);
	values[1]->setValue(y);
	values[2]->setValue(z);
	vec.setArgument(0,values[0]);
	vec.setArgument(1,values[1]);
	vec.setArgument(2,values[2]);
}

void Solid::deleteVector(Vector &del){		//TODO erase this when Simon builds his own Vector destructor
	for(int i=0;i<3;i++){
		if(del.getArgument(i)!=NULL)free(del.getArgument(i));
	}
}*/
