/*
 * vectorproduct.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef VECTORPRODUCT_H_
#define VECTORPRODUCT_H_

namespace kissms {

/**
 *
 */
class Vectorproduct : public ArgumentsTwo {

public:
	Vectorproduct();
	virtual ~Vectorproduct();

	/**
	 *
	 */
	Vector* getVector();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual std::string getQuality();

};

}


#endif /* VECTORPRODUCT_H_ */
