/*
 * sinus.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef SINUS_H_
#define SINUS_H_


namespace kissms {

class Sinus : public ArgumentsOne {

public:
	Sinus();
	virtual ~Sinus();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();


};

}


#endif /* SINUS_H_ */
