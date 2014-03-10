/*
 * cosinus.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef COSINUS_H_
#define COSINUS_H_


namespace kissms {

/**
 * @brief Component representing the mathematical cosinus-function
 */
class Cosinus : public ArgumentsOne {

public:
	Cosinus();
	virtual ~Cosinus();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual std::string getQuality();

};

}


#endif /* COSINUS_H_ */
