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

int reverse(int k){
	if(k==0){
		return 1;
	}else if(k==1){
		return 0;
	}
	return -1;
}

Variable** Physiccore::addInteractiveForceVarFromSolidToRodOfAnchor(Anchor a){
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

		a.getLink()->setHasForce(true);

		return v;
	}
	return 0;
}

int Physiccore::fillEquationSystem(){
	for(unsigned int p=0;p<elements.size();p++)systemEquationsPerElement.push_back(new SystemEquations);
	//	printf("elements.size() %d\n",elements.size());
	//	printf("systemEquationsPerElement.size() %d\n",systemEquationsPerElement.size());

	for(unsigned int i=0;i<elements.size();i++){
		if(elements.at(i)->getType()==ROD){
			if((elements.at(i)->getAnchors().at(0).getLink()==NULL && elements.at(i)->getAnchors().at(0).getGrounded()==false) || (elements.at(i)->getAnchors().at(1).getLink()==NULL && elements.at(i)->getAnchors().at(1).getGrounded()==false)){
				return -1;	//one anchor is neither grounded nor linked
			}
			if(elements.at(i)->getAnchors().at(0).getLink()!=NULL && elements.at(i)->getAnchors().at(0).getGrounded()==false){	//first anchor is linked and not grounded
				Variable** v1=addInteractiveForceVarFromSolidToRodOfAnchor(elements.at(i)->getAnchors().at(0));
				if(elements.at(i)->getAnchors().at(1).getLink()!=NULL && elements.at(i)->getAnchors().at(1).getGrounded()==false){	//second anchor is linked and not grounded
					Variable** v2=addInteractiveForceVarFromSolidToRodOfAnchor(elements.at(i)->getAnchors().at(1));

					Equation *e1=new Equation();
					Negation *n1=new Negation();
					n1->setArgument(v1[0]);
					e1->setArguments(n1,v2[0]);

					Equation *e2=new Equation();
					Negation *n2=new Negation();
					n2->setArgument(v1[1]);
					e2->setArguments(n2,v2[1]);

					equationSystem.addEquation(e1);
					equationSystem.addEquation(e2);
				}
			}else if(elements.at(i)->getAnchors().at(0).getGrounded()){		//first anchor is grounded
				if(elements.at(i)->getAnchors().at(1).getLink()!=NULL && elements.at(i)->getAnchors().at(1).getGrounded()==false){	//second anchor is linked and not grounded
					addInteractiveForceVarFromSolidToRodOfAnchor(elements.at(i)->getAnchors().at(1));
				}
			}
		}else if(elements.at(i)->getType()==RIGIDRECT){
			int groundCount=0;
			int linkCount=0;
			//			int groundNum=-4;
			for(unsigned int j=0;j<elements.at(i)->getAnchors().size();j++){
				if(elements.at(i)->getAnchors().at(j).getGrounded()){
					groundCount++;
					//					groundNum=j;
				}
				if(elements.at(i)->getAnchors().at(j).getLink()!=NULL){
					linkCount++;
				}
			}
			//			if(groundCount<2){
			for(unsigned int j=0;j<elements.at(i)->getAnchors().size();j++){
				//					printf("%d\n",elements.at(i)->getAnchors().at(j).getLink());
				//					printf("%d\n",elements.at(i)->getAnchors().at(j).getHasForce()==false);
				//					printf("%d\n",elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getType());
				if(elements.at(i)->getAnchors().at(j).getHasForce()==false && ((elements.at(i)->getAnchors().at(j).getLink()!= NULL && elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getType()!=ROD) || elements.at(i)->getAnchors().at(j).getGrounded()) ){
					Variable *fx2=new Variable();
					stringstream fx2Name;
					Variable *fy2=new Variable();
					stringstream fy2Name;
					if(elements.at(i)->getAnchors().at(j).getLink()==NULL){
						fx2Name << i << "toGroundX" << j;
						fy2Name << i << "toGroundY" << j;
					}
					if(elements.at(i)->getAnchors().at(j).getLink()!= NULL && elements.at(i)->getAnchors().at(j).getLink()->getHasForce()==false){
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

						elements.at(elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId())->addForces(fOrigin,elements.at(i)->getAnchors().at(j).getOrigin()[X],elements.at(i)->getAnchors().at(j).getOrigin()[Y],0);
						systemEquationsPerElement.at(elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId())->xVariables.push_back(fx1);		//todo anscheinend schreibt er die in das elements.at(i)
						systemEquationsPerElement.at(elements.at(i)->getAnchors().at(j).getLink()->getPlink()->getId())->yVariables.push_back(fy1);
						elements.at(i)->getAnchors().at(j).getLink()->setHasForce(true);
					}
					fx2->setName((char*)fx2Name.str().c_str());
					fy2->setName((char*)fy2Name.str().c_str());
					systemEquationsPerElement.at(i)->xVariables.push_back(fx2);
					systemEquationsPerElement.at(i)->yVariables.push_back(fy2);
					elements.at(i)->addForces(fOrigin,elements.at(i)->getAnchors().at(j).getOrigin()[X],elements.at(i)->getAnchors().at(j).getOrigin()[Y],0);
					elements.at(i)->getAnchorAddr(j)->setHasForce(true);
				}
			}
			//			if(groundCount==0){		// Rigidrect is not grounded
			//				if(linkCount==0)return -2;		// this Rigidrect is useless
			//			}else if(groundCount==1){		// Rigidrect is single-grounded
			//				if(linkCount==0)return -2;		// this Rigidrect is useless
			//			}
			//			}

		}
	}

	for(unsigned int i=0;i<elements.size();i++){
		if(elements.at(i)->getType()!=ROD){
			Equation *xForceEq=new Equation();
			Addition *xForceAd=new Addition();
			Equation *yForceEq=new Equation();
			Addition *yForceAd=new Addition();
			Equation *torqueEq=new Equation();
			Constant *nG = new Constant();
			Constant *zero = new Constant();
			zero->setValue(0);
			nG->setValue(elements.at(i)->getMass()*GRAVITY);

			if(systemEquationsPerElement.at(i)->xVariables.size()==1){
				xForceEq->setArguments(systemEquationsPerElement.at(i)->xVariables.at(0),zero);
				yForceEq->setArguments(systemEquationsPerElement.at(i)->yVariables.at(0),nG);

				Addition *tempAd1=new Addition();
				Multiplication *tempMu11=new Multiplication();
				Multiplication *tempMu12=new Multiplication();
				Constant *cx1=new Constant();
				Constant *cy1=new Constant();

				cx1->setValue(elements.at(i)->getForces(fOrigin,1,X)-elements.at(i)->getCenter(X));
				cy1->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,1,Y));

				tempMu11->setArguments(cx1,systemEquationsPerElement.at(i)->yVariables.at(0));
				tempMu12->setArguments(cy1,systemEquationsPerElement.at(i)->xVariables.at(0));

				tempAd1->setArguments(tempMu11,tempMu12);
				torqueEq->setArguments(tempAd1,zero);
			}else if(systemEquationsPerElement.at(i)->xVariables.size()==2){
				xForceAd->setArguments(systemEquationsPerElement.at(i)->xVariables.at(0),systemEquationsPerElement.at(i)->xVariables.at(1));
				yForceAd->setArguments(systemEquationsPerElement.at(i)->yVariables.at(0),systemEquationsPerElement.at(i)->yVariables.at(1));
				xForceEq->setArguments(xForceAd,zero);
				yForceEq->setArguments(yForceAd,nG);

				Addition *tempAd21=new Addition();
				Multiplication *tempMu211=new Multiplication();
				Multiplication *tempMu221=new Multiplication();
				Constant *cx21=new Constant();
				Constant *cy21=new Constant();

				cx21->setValue(elements.at(i)->getForces(fOrigin,1,X)-elements.at(i)->getCenter(X));
				cy21->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,1,Y));

				tempMu211->setArguments(cx21,systemEquationsPerElement.at(i)->yVariables.at(0));
				tempMu221->setArguments(cy21,systemEquationsPerElement.at(i)->xVariables.at(0));

				tempAd21->setArguments(tempMu211,tempMu221);

				Addition *tempAd22=new Addition();
				Multiplication *tempMu212=new Multiplication();
				Multiplication *tempMu222=new Multiplication();
				Constant *cx22=new Constant();
				Constant *cy22=new Constant();

				cx22->setValue(elements.at(i)->getForces(fOrigin,2,X)-elements.at(i)->getCenter(X));
				cy22->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,2,Y));

				tempMu212->setArguments(cx22,systemEquationsPerElement.at(i)->yVariables.at(1));
				tempMu222->setArguments(cy22,systemEquationsPerElement.at(i)->xVariables.at(1));

				tempAd22->setArguments(tempMu212,tempMu222);

				Addition *adfin2=new Addition();
				adfin2->setArguments(tempAd21,tempAd22);

				torqueEq->setArguments(adfin2,zero);
			}else if(systemEquationsPerElement.at(i)->xVariables.size()==3){
				Addition *xTemp3=new Addition();
				Addition *yTemp3=new Addition();
				xTemp3->setArguments(systemEquationsPerElement.at(i)->xVariables.at(1),systemEquationsPerElement.at(i)->xVariables.at(2));
				yTemp3->setArguments(systemEquationsPerElement.at(i)->yVariables.at(1),systemEquationsPerElement.at(i)->yVariables.at(2));
				xForceAd->setArguments(systemEquationsPerElement.at(i)->xVariables.at(0),xTemp3);
				yForceAd->setArguments(systemEquationsPerElement.at(i)->yVariables.at(0),yTemp3);
				xForceEq->setArguments(xForceAd,zero);
				yForceEq->setArguments(yForceAd,nG);

				Addition *tempAd31=new Addition();
				Multiplication *tempMu311=new Multiplication();
				Multiplication *tempMu321=new Multiplication();
				Constant *cx31=new Constant();
				Constant *cy31=new Constant();

				cx31->setValue(elements.at(i)->getForces(fOrigin,1,X)-elements.at(i)->getCenter(X));
				cy31->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,1,Y));

				tempMu311->setArguments(cx31,systemEquationsPerElement.at(i)->yVariables.at(0));
				tempMu321->setArguments(cy31,systemEquationsPerElement.at(i)->xVariables.at(0));

				tempAd31->setArguments(tempMu311,tempMu321);

				Addition *tempAd32=new Addition();
				Multiplication *tempMu312=new Multiplication();
				Multiplication *tempMu322=new Multiplication();
				Constant *cx32=new Constant();
				Constant *cy32=new Constant();

				cx32->setValue(elements.at(i)->getForces(fOrigin,2,X)-elements.at(i)->getCenter(X));
				cy32->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,2,Y));

				tempMu312->setArguments(cx32,systemEquationsPerElement.at(i)->yVariables.at(1));
				tempMu322->setArguments(cy32,systemEquationsPerElement.at(i)->xVariables.at(1));

				tempAd32->setArguments(tempMu312,tempMu322);

				Addition *tempAd33=new Addition();
				Multiplication *tempMu313=new Multiplication();
				Multiplication *tempMu323=new Multiplication();
				Constant *cx33=new Constant();
				Constant *cy33=new Constant();

				cx33->setValue(elements.at(i)->getForces(fOrigin,3,X)-elements.at(i)->getCenter(X));
				cy33->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,3,Y));

				tempMu313->setArguments(cx33,systemEquationsPerElement.at(i)->yVariables.at(2));
				tempMu323->setArguments(cy33,systemEquationsPerElement.at(i)->xVariables.at(2));

				tempAd33->setArguments(tempMu313,tempMu323);

				Addition *adfin31=new Addition();
				adfin31->setArguments(tempAd31,tempAd32);

				Addition *adfin32=new Addition();
				adfin32->setArguments(adfin31,tempAd33);

				torqueEq->setArguments(adfin32,zero);
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

				Addition *tempAd41=new Addition();
				Multiplication *tempMu411=new Multiplication();
				Multiplication *tempMu421=new Multiplication();
				Constant *cx41=new Constant();
				Constant *cy41=new Constant();

				cx41->setValue(elements.at(i)->getForces(fOrigin,1,X)-elements.at(i)->getCenter(X));
				cy41->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,1,Y));

				tempMu411->setArguments(cx41,systemEquationsPerElement.at(i)->yVariables.at(0));
				tempMu421->setArguments(cy41,systemEquationsPerElement.at(i)->xVariables.at(0));

				tempAd41->setArguments(tempMu411,tempMu421);

				Addition *tempAd42=new Addition();
				Multiplication *tempMu412=new Multiplication();
				Multiplication *tempMu422=new Multiplication();
				Constant *cx42=new Constant();
				Constant *cy42=new Constant();

				cx42->setValue(elements.at(i)->getForces(fOrigin,2,X)-elements.at(i)->getCenter(X));
				cy42->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,2,Y));

				tempMu412->setArguments(cx42,systemEquationsPerElement.at(i)->yVariables.at(1));
				tempMu422->setArguments(cy42,systemEquationsPerElement.at(i)->xVariables.at(1));

				tempAd42->setArguments(tempMu412,tempMu422);

				Addition *tempAd43=new Addition();
				Multiplication *tempMu413=new Multiplication();
				Multiplication *tempMu423=new Multiplication();
				Constant *cx43=new Constant();
				Constant *cy43=new Constant();

				cx43->setValue(elements.at(i)->getForces(fOrigin,3,X)-elements.at(i)->getCenter(X));
				cy43->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,3,Y));

				tempMu413->setArguments(cx43,systemEquationsPerElement.at(i)->yVariables.at(2));
				tempMu423->setArguments(cy43,systemEquationsPerElement.at(i)->xVariables.at(2));

				tempAd43->setArguments(tempMu413,tempMu423);

				Addition *tempAd44=new Addition();
				Multiplication *tempMu414=new Multiplication();
				Multiplication *tempMu424=new Multiplication();
				Constant *cx44=new Constant();
				Constant *cy44=new Constant();

				cx44->setValue(elements.at(i)->getForces(fOrigin,4,X)-elements.at(i)->getCenter(X));
				cy44->setValue(-elements.at(i)->getCenter(Y)+elements.at(i)->getForces(fOrigin,4,Y));

				tempMu414->setArguments(cx44,systemEquationsPerElement.at(i)->yVariables.at(3));
				tempMu424->setArguments(cy44,systemEquationsPerElement.at(i)->xVariables.at(3));

				tempAd44->setArguments(tempMu414,tempMu424);

				Addition *adfin41=new Addition();
				adfin41->setArguments(tempAd41,tempAd42);

				Addition *adfin42=new Addition();
				adfin42->setArguments(adfin41,tempAd43);

				Addition *adfin43=new Addition();
				adfin43->setArguments(adfin42,tempAd44);

				torqueEq->setArguments(adfin43,zero);
			}

			equationSystem.addEquation(xForceEq);
			equationSystem.addEquation(yForceEq);
			equationSystem.addEquation(torqueEq);
		}
	}
	return 0;
}

void Physiccore::groundHoveredAnchors(int x, int y){
	for(unsigned int i=0;i<elements.size();i++){
		for(unsigned int j=0;j<elements.at(i)->getAnchors().size();j++){
			if(abs(elements.at(i)->getAnchors().at(j).getOrigin()[0]-x)<10 && abs(elements.at(i)->getAnchors().at(j).getOrigin()[1]-y)<10){
				elements.at(i)->setAnchorGrounded(j,true);
				if(elements.at(i)->getType()==RIGIDRECT){
					int countGrounded=0;
					for(unsigned int k=0;k<elements.at(i)->getAnchors().size();k++){
						if(elements.at(i)->getAnchors().at(k).getGrounded()){
							countGrounded++;
						}
					}
					if(countGrounded>1){
						for(unsigned int k=0;k<elements.at(i)->getAnchors().size();k++){
							elements.at(i)->setAnchorGrounded(k,true);
						}
					}
				}
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
			for(unsigned int i=0;i<systemEquationsPerElement.size();i++){
				printf("%d:\n",i);
						for(unsigned int j=0;j<systemEquationsPerElement.at(i)->xVariables.size();j++){
							printf("%s\n",systemEquationsPerElement.at(i)->xVariables.at(j)->getName());
							printf("%s\n",systemEquationsPerElement.at(i)->yVariables.at(j)->getName());
						}
				printf("\n");
			}

	for(unsigned int i=0;i<elements.size();i++){
		for(unsigned int j=0;j<systemEquationsPerElement.at(i)->xVariables.size();j++){
			equationSystem.calculateFor(systemEquationsPerElement.at(i)->xVariables.at(j));
			equationSystem.calculateFor(systemEquationsPerElement.at(i)->yVariables.at(j));
			elements.at(i)->addForces(fValue,systemEquationsPerElement.at(i)->xVariables.at(j)->getQuantity(),-(systemEquationsPerElement.at(i)->yVariables.at(j)->getQuantity()),0);
			printf("\n%s : %f\n",systemEquationsPerElement.at(i)->xVariables.at(j)->getName(),systemEquationsPerElement.at(i)->xVariables.at(j)->getQuantity());
			printf("\n%s : %f",systemEquationsPerElement.at(i)->yVariables.at(j)->getName(),systemEquationsPerElement.at(i)->yVariables.at(j)->getQuantity());
		}
	}

	draftElements();
}
