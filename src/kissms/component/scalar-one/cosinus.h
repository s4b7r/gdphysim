/*
 * cosinus.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef COSINUS_H_
#define COSINUS_H_


namespace kissms {

class Cosinus : public ArgumentsOne {

public:
	Cosinus();
	virtual ~Cosinus();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();


};

}


#endif /* COSINUS_H_ */
