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
 * @author sbekemeier
 *
 *
 */
class Component {

public:
	Component(  );
	virtual ~Component(  );

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
	bool isCalculable(  );

	/**
	 * @brief Checks whether the Component is representable by a numerical value
	 * @retval True The Component is representable by a numerical value
	 * @retval False The Component is not representable by a numerical value
	 *
	 * Checks all child-Components whether they are representable by numerical values.
	 *
	 * @see isCalculable()
	 */
	bool isQuantifiable(  );

};

}


#endif /* COMPONENT_H_ */
