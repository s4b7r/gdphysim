/*
 * variable.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_


namespace kissms {

/**
 * @brief Component representing a single variable value
 */
class Variable : public Component {

public:
	Variable();
	virtual ~Variable();

	/**
	 * @brief Set a placeholder string as the Variable's value
	 * @param value A zero-terminated character array representing the placeholder string
	 */
	void setVariable( char *value );

	/**
	 * @brief Set an integer value as the Variable's value
	 * @param value The Variable's new integer value
	 */
	void setVariable( int value );

	/**
	 * @brief Set a double value as the Variable's value
	 * @param value The Variable's new double value
	 */
	void setVariable( double value );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

};

}


#endif /* VARIABLE_H_ */
