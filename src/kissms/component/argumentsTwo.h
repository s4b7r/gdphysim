/*
 * argumentsTwo.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef ARGUMENTSTWO_H_
#define ARGUMENTSTWO_H_


namespace kissms {

/**
 * @brief Representation of Components taking two arguments
 * @author sbekemeier
 *
 *
 */
class ArgumentsTwo : public Component {

public:
	ArgumentsTwo(  ) { };
	virtual ~ArgumentsTwo(  );

	/**
	 * @brief
	 * @param argument Component on this component's left side
	 * @retval Successful
	 * @retval Failure
	 *
	 */
	ResultCode setLeft( const Component *argument );
	/**
	 * @brief
	 * @details
	 * @param argument Component on this component's right side
	 * @retval Successful
	 * @retval Failure
	 */
	ResultCode setRight( const Component *argument );
	/**
	 * @brief
	 * @param left Component on this component's left side
	 * @param right Component on this component's right side
	 * @retval Successful
	 * @retval Failure
	 *
	 */
	ResultCode setArguments( const Component *left, const Component *right );

};

}


#endif /* ARGUMENTSTWO_H_ */
