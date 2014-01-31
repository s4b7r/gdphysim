/*
 * argumentsOne.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef ARGUMENTSONE_H_
#define ARGUMENTSONE_H_


namespace kissms {

/**
 * @brief Representation of Components taking one argument
 * @author sbekemeier
 *
 *
 */
class ArgumentsOne : public Component {

public:
	virtual ArgumentsOne(  ) = 0;
	virtual ~ArgumentsOne(  ) = 0;

	/**
	 * @brief
	 * @param argument This component's argument
	 *
	 *
	 */
	void setArgument( Component *argument );

};

}


#endif /* ARGUMENTSONE_H_ */
