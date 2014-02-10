/*
 * multiplication.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef MULTIPLICATION_H_
#define MULTIPLICATION_H_


namespace kissms {

class Multiplication : public ArgumentsTwo {

public:
	Multiplication();
	virtual ~Multiplication();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

};

}


#endif /* MULTIPLICATION_H_ */
