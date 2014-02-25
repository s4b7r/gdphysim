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
	 *
	 */
	void setArgument( int index, Component *value );

	/**
	 *
	 */
	Component* getArgument( int index );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ResultCode calculate();

	virtual ComponentType getType();

	virtual bool hasChild( Component *child );

	virtual bool isVectorial();

	virtual std::string getQuality();

private:
	/**
	 *
	 */
	Component *arguments[3];

};

}


#endif /* VECTOR_H_ */
