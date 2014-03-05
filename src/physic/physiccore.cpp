/*
 * physiccore.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: kevin
 */

#include "physic/physiccore.h"
#include "math.h"

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

void Physiccore::computeInteractiveForces(){

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
		((Anchor*)links[0])->setLink(links[1]);
		((Anchor*)links[1])->setLink(links[0]);
	}
}
