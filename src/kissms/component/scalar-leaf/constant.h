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
	/**
	 * @brief Enumeration of a Constant's possible types
	 */
	enum Type {Unspecified = 0,String,Integer,Double};
	/** @var kissms::Constant::Type kissms::Constant::Unspecified
	 * @brief The constant is not specified in any way
	 */
	/** @var kissms::Constant::Type kissms::Constant::String
	 * @brief The constant is specified as a placeholder string
	 */
	/** @var kissms::Constant::Type kissms::Constant::Integer
	 * @brief The constant is an integer value
	 */
	/** @var kissms::Constant::Type kissms::Constant::Double
	 * @brief The constant is an floating point value
	 */

	Constant();
	virtual ~Constant();

	/**
	 * @brief Set the Constant's value
	 * @param value A zero-terminated character array representing the Constant's value
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

	/**
	 * @brief Resets the Constant's value
	 */
	void resetValue();

	/**
	 * @brief Returns the Constant's value and it's type
	 * @param value Pointer which will point to the Constant's value
	 * @return The Constant's type
	 */
	Type getValue( void *value );

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
	Type type;
	void *value;

};

}


#endif /* CONSTANT_H_ */
