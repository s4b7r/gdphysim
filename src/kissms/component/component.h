/*
 * component.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_


namespace kissms {

/**
 * @brief Representation of a mathematical component in an Equation
 *
 *
 */
class Component {

public:
	Component();
	virtual ~Component();

	/**
	 * @brief Checks whether the Component is calculable
	 * @retval True The Component contains no unresolved Variables
	 * @retval False The Component contains at least one unresolved Variable
	 *
	 * Checks all child-Components for unresolved Variables. In case of finding at least one
	 * unresolved Variable the Component is not calculable. Finding no unresolved Variables
	 * does not proove the Component as representable by a numerical value.
	 *
	 * @see isQuantifiable()
	 */
	virtual bool isCalculable() = 0;

	/**
	 * @brief Checks whether the Component is representable by a numerical value
	 * @retval True The Component is representable by a numerical value
	 * @retval False The Component is not representable by a numerical value
	 *
	 * Checks all child-Components whether they are representable by numerical values.
	 *
	 * @see isCalculable()
	 */
	virtual bool isQuantifiable() = 0;

	/**
	 * @brief Returns Components for reformation
	 * @param variable Variable for which the Component shall reform itself
	 * @param newSide New Component replacing the Component on this side of the Equation
	 * @param otherSide Component for reformation of the Equation's other side
	 * @param placeholder Placeholder which shall be replaced by the Equation's old other side
	 * @return ResultCode
	 */
	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide ) = 0;

	/**
	 * @brief Calculates the Component's numerical value
	 * @return ResultCode
	 *
	 * Calculates the Component's numerical value as far as the Component's childs allow this.
	 */
	virtual ResultCode calculate() = 0;

	/**
	 *
	 */
	double getQuantity();

	/**
	 *
	 */
	virtual ComponentType getType();

	/**
	 *
	 */
	virtual bool hasChild( Component *child ) = 0;

protected:
	double quantity;

};

}


#endif /* COMPONENT_H_ */
