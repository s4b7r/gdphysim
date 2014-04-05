/*
 * physiccore.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: kevin
 */

#include "physic/physiccore.h"
#include "physic/solids/rod.h"
#include "math.h"

using kissms::Multiplication;
using kissms::Constant;
using kissms::Negation;
using kissms::Addition;
using std::stringstream;

//int* copyNewArray(int* src, int l){
//	int *ret= new int[l];
//	for(int i=0;i<l;i++){
//		ret[i]=src[i];
//	}
//	return ret;
//}

void Physiccore::setAnchorsPosition(){
	anchorPositions.clear();
	for(unsigned int i=0;i<elements.size();i++){
		for(unsigned int j=0;j<elements.at(i)->getAnchors().size();j++){
			//			printf("%d\n", elements.at(i).getAnchors().at(j).getOrigin()[0]);
			anchorPositions.push_back(elements.at(i)->getAnchors().at(j).getOrigin());
		}
	}
}

vector<int*> Physiccore::getAnchorsPosition(){
	return vector<int*>(anchorPositions);
}

void Physiccore::draftElements(){
	for(unsigned int i=0;i<elements.size();i++){
		elements.at(i)->draft();
	}
}

void Physiccore::deleteHoveredElements(int x, int y){
	for(unsigned int i=0;i<elements.size();i++){
		for(unsigned int j=0;j<elements.at(i)->getAnchors().size();j++){
			if(abs(elements.at(i)->getAnchors().at(j).getOrigin()[0]-x)<10 && abs(elements.at(i)->getAnchors().at(j).getOrigin()[1]-y)){
				elements.erase(elements.begin()+i);
				break;
			}
		}
	}
	setAnchorsPosition();
}

//int reverse(int k){
//	if(k==0){
//		return 1;
//	}else if(k==1){
//		return 0;
//	}
//	return -1;
//}

/*Variable** Physiccore::addInteractiveForceVarFromSolidToRodOfAnchor(Anchor a){
	if(!(a.getLink()->getHasForce())){
		Variable* v[2];

		Variable *fx=new Variable();
		stringstream fxName;
		fxName << a.getLink()->getPlink()->getId() << "toRodX" << a.getPlink()->getId();
		fx->setName((char*)fxName.str().c_str());
		Variable *fy=new Variable();
		stringstream fyName;
		fyName << a.getLink()->getPlink()->getId() << "toRodY" << a.getPlink()->getId();
		fy->setName((char*)fyName.str().c_str());
		Variable *f=new Variable();
		stringstream fName;
		fName << a.getLink()->getPlink()->getId() << "toRod" << a.getPlink()->getId();
		f->setName((char*)fName.str().c_str());
		v[0]=fx;
		v[1]=fy;

		Equation *ex=new Equation();
		Multiplication *mx= new Multiplication();
		Constant *cx= new Constant();
		cx->setValue((double)(a.getPlink()->getCenter(X)-a.getOrigin()[X])/(sqrt(pow((double)(a.getPlink()->getCenter(X)-a.getOrigin()[X]),2)+pow((double)(-a.getPlink()->getCenter(Y)+a.getOrigin()[Y]),2))));
		mx->setArguments(f,cx);
		ex->setArguments(fx,mx);

		Equation *ey=new Equation();
		Multiplication *my= new Multiplication();
		Constant *cy= new Constant();
		cy->setValue((double)(-a.getPlink()->getCenter(Y)+a.getOrigin()[Y])/(sqrt(pow((double)(a.getPlink()->getCenter(X)-a.getOrigin()[X]),2)+pow((double)(-a.getPlink()->getCenter(Y)+a.getOrigin()[Y]),2))));
		my->setArguments(f,cy);
		ey->setArguments(fy,my);

		equationSystem.addEquation(ex);
		equationSystem.addEquation(ey);

		systemEquationsPerElement.at(a.getLink()->getPlink()->getId())->xVariables.push_back(fx);
		systemEquationsPerElement.at(a.getLink()->getPlink()->getId())->yVariables.push_back(fy);
		elements.at(a.getLink()->getPlink()->getId())->addForces(fOrigin,a.getOrigin()[X],a.getOrigin()[Y],0);
		systemEquationsPerElement.at(a.getLink()->getPlink()->getId())->varCount++;
		a.getLink()->setHasForce(true);

		return v;
	}
	return 0;
}*/

void Physiccore::addTorqueEquation(int id){
	Equation *torqueEq=new Equation();
	int x=rand()%1000+1;
	int y=rand()%1000+1;
	Constant *tG = new Constant();
	Constant *zero = new Constant();
	zero->setValue(0);
	tG->setValue(elements.at(id)->getMass()*GRAVITY*(elements.at(id)->getCenter(X)-x));		//negatives Drehmoment von der Gewichtskraft verursacht
	Addition *tempAd1=new Addition();
	Addition *tempAd2=new Addition();
	Addition *tempAd3=new Addition();
	Addition *tempAd4=new Addition();
	Addition *tempAd12=new Addition();
	Addition *tempAd34=new Addition();
	Addition *tempAdBoss=new Addition();

	Multiplication *mx[4];
	Multiplication *my[4];
	for(int k=0;k<4;k++){
		mx[k]=new Multiplication();
		mx[k]->setArguments(zero,zero);
		my[k]=new Multiplication();
		my[k]->setArguments(zero,zero);
	}
	Constant *cx[4];
	Constant *cy[4];
	for(int k=0;k<4;k++){
		cx[k]=new Constant();
		cx[k]->setValue(0);
		cy[k]=new Constant();
		cy[k]->setValue(0);
	}

	for(unsigned int i=0;i<systemEquationsPerElement.at(id)->xVariables.size();i++){
		cx[i]->setValue(elements.at(id)->getForces(fOrigin,i+1,X)-x);
		cy[i]->setValue(-y+elements.at(id)->getForces(fOrigin,i+1,Y));
		mx[i]->setArguments(cx[i],systemEquationsPerElement.at(id)->yVariables.at(i));
		my[i]->setArguments(cy[i],systemEquationsPerElement.at(id)->xVariables.at(i));
	}

	tempAd1->setArguments(mx[0],my[0]);
	tempAd2->setArguments(mx[1],my[1]);
	tempAd3->setArguments(mx[2],my[2]);
	tempAd4->setArguments(mx[3],my[3]);
	tempAd34->setArguments(tempAd3,tempAd4);
	tempAd12->setArguments(tempAd1,tempAd2);
	tempAdBoss->setArguments(tempAd12,tempAd34);
	torqueEq->setArguments(tempAdBoss,tG);
	torqueEq->setDebugId(12);
	equationSystem.addEquation(torqueEq);
}

int Physiccore::fillEquationSystem(){
	for(unsigned int p=0;p<elements.size();p++){
		systemEquationsPerElement.push_back(new SystemEquations);
		systemEquationsPerElement.at(p)->varCount=0;
	}
	//	printf("elements.size() %d\n",elements.size());
	//	printf("systemEquationsPerElement.size() %d\n",systemEquationsPerElement.size());

	for(unsigned int i=0;i<elements.size();i++){
		for(unsigned int j=0;j<elements.at(i)->getAnchors().size();j++){
			if((elements.at(i)->getAnchors().at(j).getLink()!=NULL || elements.at(i)->getAnchors().at(j).getGrounded()) && !elements.at(i)->getAnchors().at(j).getHasForce()){
				Variable *fx2=new Variable();
				stringstream fx2Name;
				Variable *fy2=new Variable();
				stringstream fy2Name;

				//if the current anchor is grounded
				if(elements.at(i)->getAnchors().at(j).getLink()==NULL){
					fx2Name << i << "toGroundX" << j;
					fy2Name << i << "toGroundY" << j;

					fx2->setName((char*)fx2Name.str().c_str());
					fy2->setName((char*)fy2Name.str().c_str());
				}

				//if the current anchor is linked and has not been edited
				if(elements.at(i)->getAnchors().at(j).getLink()!= NULL && elements.at(i)->getAnchors().at(j).getLink()->getHasForce()==false){

					//Create variables for the linked body and name them
					Variable *fx1=new Variable();
					stringstream fx1Name;
					fx1Name << elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId() << "toRectX" << i;
					fx1->setName((char*)fx1Name.str().c_str());

					Variable *fy1=new Variable();
					stringstream fy1Name;
					fy1Name << elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId() << "toRectY" << i;
					fy1->setName((char*)fy1Name.str().c_str());

					fx2Name << i << "toX" << elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId();
					fy2Name << i << "toY" << elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId();

					fx2->setName((char*)fx2Name.str().c_str());
					fy2->setName((char*)fy2Name.str().c_str());

					//add the equations for the interactive forces to the equation system
					Equation *ex=new Equation();
					Negation *nx=new Negation();
					nx->setArgument(fx1);
					ex->setArguments(nx,fx2);
					equationSystem.addEquation(ex);

					Equation *ey=new Equation();
					Negation *ny=new Negation();
					ny->setArgument(fy1);
					ey->setArguments(ny,fy2);
					equationSystem.addEquation(ey);

					//add the coordinates for the interactive force originating at the anchor of the linked solid body
					elements.at(elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId())->addForces(fOrigin,elements.at(i)->getAnchors().at(j).getOrigin()[X],elements.at(i)->getAnchors().at(j).getOrigin()[Y],0);

					//add the created variables to the linked body variables
					systemEquationsPerElement.at(elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId())->xVariables.push_back(fx1);
					systemEquationsPerElement.at(elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId())->yVariables.push_back(fy1);

					//mark the anchor of the linked body as edited
					elements.at(i)->getAnchors().at(j).getLink()->setHasForce(true);
				}

				//add the created variables to the body of the current iteration
				systemEquationsPerElement.at(i)->xVariables.push_back(fx2);
				systemEquationsPerElement.at(i)->yVariables.push_back(fy2);

				//add coordinates of the force of the current anchor to the current body
				elements.at(i)->addForces(fOrigin,elements.at(i)->getAnchors().at(j).getOrigin()[X],elements.at(i)->getAnchors().at(j).getOrigin()[Y],0);

				//mark current anchor as edited
				elements.at(i)->getAnchorAddr(j)->setHasForce(true);
			}
		}
	}

	//Ausgabe der gefundenen Kräfte
	//	for(unsigned int i=0;i<elements.size();i++){
	//		for(int k=0;k<elements.at(i)->getForcesSize(fOrigin);k++){
	//			printf("%d %d %d",elements.at(i)->getType(), elements.at(i)->getForces(fOrigin,k,X),elements.at(i)->getForces(fOrigin,k,Y));
	//			printf(", Values: %d %d\n", elements.at(i)->getForces(fValue,k,X),elements.at(i)->getForces(fValue,k,Y));
	//		}
	//	}


	//add the force equations for every solid body to the equation system
	for(unsigned int i=0;i<elements.size();i++){
		Equation *xForceEq=new Equation();
		Addition *xForceAd=new Addition();
		Equation *yForceEq=new Equation();
		Addition *yForceAd=new Addition();

		Constant *nG = new Constant();
		Constant *zero = new Constant();
		zero->setValue(0);
		nG->setValue(elements.at(i)->getMass()*GRAVITY);

		if(elements.at(i)->getVariance()==3){
			addTorqueEquation(i);
		}

		if(systemEquationsPerElement.at(i)->xVariables.size()==1){
			xForceEq->setArguments(systemEquationsPerElement.at(i)->xVariables.at(0),zero);
			yForceEq->setArguments(systemEquationsPerElement.at(i)->yVariables.at(0),nG);

		}else if(systemEquationsPerElement.at(i)->xVariables.size()==2){
			xForceAd->setArguments(systemEquationsPerElement.at(i)->xVariables.at(0),systemEquationsPerElement.at(i)->xVariables.at(1));
			yForceAd->setArguments(systemEquationsPerElement.at(i)->yVariables.at(0),systemEquationsPerElement.at(i)->yVariables.at(1));
			xForceEq->setArguments(xForceAd,zero);
			yForceEq->setArguments(yForceAd,nG);

		}else if(systemEquationsPerElement.at(i)->xVariables.size()==3){
			Addition *xTemp3=new Addition();
			Addition *yTemp3=new Addition();
			xTemp3->setArguments(systemEquationsPerElement.at(i)->xVariables.at(1),systemEquationsPerElement.at(i)->xVariables.at(2));
			yTemp3->setArguments(systemEquationsPerElement.at(i)->yVariables.at(1),systemEquationsPerElement.at(i)->yVariables.at(2));
			xForceAd->setArguments(systemEquationsPerElement.at(i)->xVariables.at(0),xTemp3);
			yForceAd->setArguments(systemEquationsPerElement.at(i)->yVariables.at(0),yTemp3);
			xForceEq->setArguments(xForceAd,zero);
			yForceEq->setArguments(yForceAd,nG);

		}else if(systemEquationsPerElement.at(i)->xVariables.size()==4){
			Addition *xTemp4=new Addition();
			Addition *yTemp4=new Addition();
			Addition *xTemp2=new Addition();
			Addition *yTemp2=new Addition();
			xTemp4->setArguments(systemEquationsPerElement.at(i)->xVariables.at(2),systemEquationsPerElement.at(i)->xVariables.at(3));
			yTemp4->setArguments(systemEquationsPerElement.at(i)->yVariables.at(2),systemEquationsPerElement.at(i)->yVariables.at(3));
			xTemp2->setArguments(systemEquationsPerElement.at(i)->xVariables.at(0),systemEquationsPerElement.at(i)->xVariables.at(1));
			yTemp2->setArguments(systemEquationsPerElement.at(i)->yVariables.at(0),systemEquationsPerElement.at(i)->yVariables.at(1));
			xForceAd->setArguments(xTemp2,xTemp4);
			yForceAd->setArguments(yTemp2,yTemp4);
			xForceEq->setArguments(xForceAd,zero);
			yForceEq->setArguments(yForceAd,nG);

		}
		equationSystem.addEquation(xForceEq);
		equationSystem.addEquation(yForceEq);
	}
	return 0;
}

void Physiccore::groundHoveredAnchors(int x, int y){
	for(unsigned int i=0;i<elements.size();i++){
		for(unsigned int j=0;j<elements.at(i)->getAnchors().size();j++){
			if(abs(elements.at(i)->getAnchors().at(j).getOrigin()[0]-x)<10 && abs(elements.at(i)->getAnchors().at(j).getOrigin()[1]-y)<10){
				elements.at(i)->setAnchorGrounded(j,true);
			}
		}
	}
}

void Physiccore::linkHoveredAnchors(int x, int y){
	Anchor* links[2]={0,0};
	int c=0;
	for(unsigned int i=0;i<elements.size();i++){
		for(unsigned int j=0;j<elements.at(i)->getAnchors().size();j++){
			if(abs(elements.at(i)->getAnchors().at(j).getOrigin()[0]-x)<10 && abs(elements.at(i)->getAnchors().at(j).getOrigin()[1]-y)<10 && c<2){
				links[c]=elements.at(i)->getAnchorAddr(j);
				c++;
				//				printf("c= %d\n",c);
			}
		}
	}
	if(c==2){
		//		printf("%d,%d - %d,%d\n",((Anchor*)links[0])->getOrigin()[0],((Anchor*)links[0])->getOrigin()[1],((Anchor*)links[1])->getOrigin()[0],((Anchor*)links[1])->getOrigin()[1]);
		((Anchor*)links[0])->setLink(links[1]);
		((Anchor*)links[1])->setLink(links[0]);
	}
}

void Physiccore::solve(){
	fillEquationSystem();
	//	for(unsigned int i=0;i<systemEquationsPerElement.size();i++){
	//		printf("%d:\n",i);
	//		for(unsigned int j=0;j<systemEquationsPerElement.at(i)->xVariables.size();j++){
	//			printf("%s\n",systemEquationsPerElement.at(i)->xVariables.at(j)->getName());
	//			printf("%s\n",systemEquationsPerElement.at(i)->yVariables.at(j)->getName());
	//		}
	//		printf("\n");
	//	}
	equationSystem.solve();
	for(unsigned int i=0;i<elements.size();i++){
		for(unsigned int j=0;j<systemEquationsPerElement.at(i)->xVariables.size();j++){
			//			equationSystem.calculateFor(systemEquationsPerElement.at(i)->xVariables.at(j));
			//			equationSystem.calculateFor(systemEquationsPerElement.at(i)->yVariables.at(j));
			elements.at(i)->addForces(fValue,systemEquationsPerElement.at(i)->xVariables.at(j)->getQuantity(),-(systemEquationsPerElement.at(i)->yVariables.at(j)->getQuantity()),0);
			//			printf("\n%s : %f\n",systemEquationsPerElement.at(i)->xVariables.at(j)->getName(),systemEquationsPerElement.at(i)->xVariables.at(j)->getQuantity());
			//			printf("\n%s : %f",systemEquationsPerElement.at(i)->yVariables.at(j)->getName(),systemEquationsPerElement.at(i)->yVariables.at(j)->getQuantity());
		}
	}
	draftElements();
	for(unsigned int h=0;h<elements.size();h++)elements.at(h)->clearSolid();
	systemEquationsPerElement.clear();
	equationSystem.clearSystem();
	anchorPositions.clear();
}
