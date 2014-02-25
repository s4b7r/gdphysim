/*
 * sinusarc.h
 *
 *  Created on: 10.02.2014
 *      Author: sieb
 */

#ifndef SINUSARC_H_
#define SINUSARC_H_


namespace kissms {

class SinusArc : public ArgumentsOne {

public:
	SinusArc();
	virtual ~SinusArc();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual char* getQuality();


};

}


#endif /* SINUSARC_H_ */
