/*
 * constant.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_


namespace kissms {

/**
 * @brief Component representing a single constant value
 */
class Constant : public Component {

public:
	Constant();
	virtual ~Constant();

	/**
	 * @brief Set the Constant's value
	 * @param name A zero-terminated character array representing the Constant's value
	 */
	void setValue( char *value );

	/**
	 * @brief Set the Constant's value
	 * @param value
	 */
	void setValue( int value );

	/**
	 * @brief Set the Constant's value
	 * @param value
	 */
	void setValue( double value );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

};

}


#endif /* CONSTANT_H_ */
