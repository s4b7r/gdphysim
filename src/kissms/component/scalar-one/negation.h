/*
 * negation.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef NEGATION_H_
#define NEGATION_H_


namespace kissms {

/**
 * @brief Component representing the negation of a single Component
 */
class Negation : public ArgumentsOne {

public:
	Negation();
	virtual ~Negation();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual char* getQuality();

};

}


#endif /* NEGATION_H_ */
