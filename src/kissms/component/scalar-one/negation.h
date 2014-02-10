/*
 * negation.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef NEGATION_H_
#define NEGATION_H_


namespace kissms {

class Negation : public ArgumentsOne {

public:
	Negation();
	virtual ~Negation();

	//virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide,
		//	Component **placeholder );
	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

};

}


#endif /* NEGATION_H_ */
