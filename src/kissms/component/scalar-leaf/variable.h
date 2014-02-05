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
	/**
	 * @brief
	 *
	 *
	 */
	enum Type {
		Unspecified = 0,
		NoValue,
		Integer,
		Double
	};
	/** @var kissms::Variable::Type kissms::Variable::Unspecified
	 * @brief
	 *
	 *
	 */
	/** @var kissms::Variable::Type kissms::Variable::NoValue
	 * @brief
	 *
	 *
	 */
	/** @var kissms::Variable::Type kissms::Variable::Integer
	 * @brief
	 *
	 *
	 */
	/** @var kissms::Variable::Type kissms::Variable::Double
	 * @brief
	 *
	 *
	 */

	Variable();
	virtual ~Variable();

	/**
	 * @brief Set the Variable's name
	 * @param name A zero-terminated character array representing the Variable's name
	 */
	void setName( char *name );

	/**
	 * @brief Set the Variable's value
	 * @param value
	 */
	void setValue( int value );

	/**
	 * @brief Set the Variable's value
	 * @param value
	 */
	void setValue( double value );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

private:
	Type type;

};

}


#endif /* VARIABLE_H_ */
