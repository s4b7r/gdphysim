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
	 * @brief Set the Variable's name
	 * @param name A zero-terminated character array representing the Variable's name
	 */
	void setVariable( char *name );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

};

}


#endif /* VARIABLE_H_ */
