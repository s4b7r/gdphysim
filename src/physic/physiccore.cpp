/*
 * physiccore.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: kevin
 */

#include "physic/physiccore.h"

void Physiccore::addElement(Solid element){
	elements.push_back(element);
	setAnchorsPosition();
}

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
		for(unsigned int j=0;j<elements.at(i).getAnchors().size();j++){
//			printf("%d\n", elements.at(i).getAnchors().at(j).getOrigin()[0]);
			anchorPositions.push_back(elements.at(i).getAnchors().at(j).getOrigin());
		}
	}
}

vector<int*> Physiccore::getAnchorsPosition(){
	return vector<int*>(anchorPositions);
}

