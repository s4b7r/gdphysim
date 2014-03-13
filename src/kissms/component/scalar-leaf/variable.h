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
		Double,
		Qualified
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
	/** @var kissms::Variable::Type kissms::Variable::Qualified
	 * @brief The Variable's quality is set
	 */

	Variable();
	virtual ~Variable();

	/**
	 * @brief Set the Variable's name
	 * @param name A zero-terminated character array representing the Variable's name
	 */
	void setName( char *name );

	/**
	 * @brief Returns the Variable's name
	 * @return A zero-terminated character array representing the Variable's name
	 */
	char* getName();

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

	/**
	 * @brief Resets the Variable's value
	 *
	 * This method reset's any numerical value assigned to this Variable.
	 * Furthermore the quality will be cleared. The Variable's name will be kept.
	 */
	void resetValue();

	/**
	 * @brief Returns the numerical value assigned to the Variable, if any
	 * @param value Value-pointer
	 * @return The value's type
	 */
	Type getValue( void **value );

	/**
	 * @brief Sets the Variable's quality
	 * @param quality A C++ string class representing the Variable's quality
	 */
	void setQuality( std::string quality );

	virtual void replace( Component *search, Component *replace );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual bool hasChild( Component *child );

	virtual bool isVectorial();

	virtual std::string getQuality();

	virtual void getVariables( std::vector<Variable*> *variables );

	virtual Component* clone();

private:
	/**
	 * @brief Variable's type as specified by enumeration type Variable::Type
	 */
	Type type;

	/**
	 * @brief The Variable's name as a zero-terminated character array
	 */
	char *name;

	/**
	 * @brief The Variable's value-pointer
	 */
	void *value;

	/**
	 * @brief The Variable's quality-string
	 */
	std::string quality;

};

}


#endif /* VARIABLE_H_ */
