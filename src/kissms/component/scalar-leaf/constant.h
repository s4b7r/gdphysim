/*
 * constant.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_


namespace kissms {

class Constant : public Component {

public:

	enum Type {Unspecified = 0,String,Integer,Double};

	Constant();
	virtual ~Constant();


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

	virtual bool isCalculable();

	virtual bool isQuantifiable();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual bool hasChild( Component *child );

	virtual bool isVectorial();

	virtual std::string getQuality();

	virtual void getVariables( std::vector<Variable*> *variables );

private:
	Type type;
	void *value;

};

}


#endif /* CONSTANT_H_ */
