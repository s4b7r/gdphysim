/*
 * cosinusarc.h
 *
 *  Created on: 10.02.2014
 *      Author: sieb
 */

#ifndef COSINUSARC_H_
#define COSINUSARC_H_


namespace kissms {

/**
 * @brief Component representing the mathematical arcus-cosinus-function
 */
class CosinusArc : public ArgumentsOne {

public:
	CosinusArc();
	virtual ~CosinusArc();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual std::string getQuality();

};

}


#endif /* COSINUSARC_H_ */
