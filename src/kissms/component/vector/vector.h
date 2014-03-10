/*
 * vector.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef VECTOR_H_
#define VECTOR_H_


namespace kissms {

/**
 *
 */
class Vector : public Component {

public:
	Vector();
	virtual ~Vector();

	/**
	 * @brief Sets the given argument of the vector
	 * @param index Index, in the range from 0 to 2, of the argument which shall be set
	 * @param value The Component which shall be set as the argument
	 */
	void setArgument( int index, Component *value );

	/**
	 * @brief Return the given argument
	 * @param index Index, in the range from 0 to 2, which argument shall be returned
	 * @return The argument from the given index
	 */
	Component* getArgument( int index );

	virtual void replace( Component* search, Component* replace );

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
	 * @brief The Vector's three arguments
	 */
	Component *arguments[3];

};

}


#endif /* VECTOR_H_ */
