/*
 * reciprocal.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef RECIPROCAL_H_
#define RECIPROCAL_H_


namespace kissms {

class Reciprocal : public ArgumentsOne {

public:
	Reciprocal();
	virtual ~Reciprocal();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

};

}


#endif /* RECIPROCAL_H_ */
