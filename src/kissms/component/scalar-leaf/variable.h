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
	 * @brief Enumeration of a Variable's possible types
	 */
	enum Type {
		Unspecified = 0,
		NoValue,
		Integer,
		Double
	};
	/** @var kissms::Variable::Type kissms::Variable::Unspecified
	 * @brief The Variable is not specified in any way
	 */
	/** @var kissms::Variable::Type kissms::Variable::NoValue
	 * @brief The Variable is named, but has no numerical value assigned to it
	 */
	/** @var kissms::Variable::Type kissms::Variable::Integer
	 * @brief The Variable has an integer value assigned to it
	 */
	/** @var kissms::Variable::Type kissms::Variable::Double
	 * @brief The Variable has an floating point value assigned to it
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

	// TODO setValue(char*) for non-quantifiable values

	/**
	 * @brief Set the Variable's value
	 * @param value
	 */
	void setValue( double value );

	/**
	 * @brief Resets the Variable's value
	 *
	 * This method reset's any numerical value assigned to this Variable.
	 * The Variable's name will be kept.
	 */
	void resetValue();

	/**
	 * @brief Returns the numerical value assigned to the Variable, if any
	 * @param value Pointer which will point to the Variable's value
	 * @return The value's type
	 */
	Type getValue( void *value );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual bool hasChild( Component *child );

	virtual bool isVectorial();

private:
	Type type;
	char *name;
	void *value;

};

}


#endif /* VARIABLE_H_ */
