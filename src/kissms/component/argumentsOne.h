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
	ArgumentsOne(  );
	virtual ~ArgumentsOne(  );

	/**
	 * @brief
	 * @param argument This component's argument
	 */
	void setArgument( Component *argument );

};

}


#endif /* ARGUMENTSONE_H_ */
