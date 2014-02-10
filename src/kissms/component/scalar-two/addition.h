/*
 * addition.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef ADDITION_H_
#define ADDITION_H_


namespace kissms {

class Addition : public ArgumentsTwo {

public:
	Addition();
	virtual ~Addition();

	//virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide,
		//	Component **placeholder );
	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

};

}


#endif /* ADDITION_H_ */
