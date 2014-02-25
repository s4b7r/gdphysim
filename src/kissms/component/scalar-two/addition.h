/*
 * addition.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef ADDITION_H_
#define ADDITION_H_


namespace kissms {

/**
 * @brief Component representing an Addition of two Components
 */
class Addition : public ArgumentsTwo {

public:
	Addition();
	virtual ~Addition();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual char* getQuality();

};

}


#endif /* ADDITION_H_ */
