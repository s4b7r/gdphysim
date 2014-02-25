/*
 * multiplication.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef MULTIPLICATION_H_
#define MULTIPLICATION_H_


namespace kissms {

/**
 * @brief Component representing a multiplication of two Components
 */
class Multiplication : public ArgumentsTwo {

public:
	Multiplication();
	virtual ~Multiplication();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual char* getQuality();

};

}


#endif /* MULTIPLICATION_H_ */
