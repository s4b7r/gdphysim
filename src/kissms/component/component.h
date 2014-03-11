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
	 * @return ResultCode
	 */
	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide ) = 0;

	/**
	 * @brief Calculates the Component's numerical value
	 * @return ResultCode
	 * @todo Implement calculation of symbolic expressions
	 *
	 * Calculates the Component's numerical value as far as the Component's childs allow this.
	 */
	virtual ResultCode calculate() = 0;

	/**
	 * @brief Returns the Component's numerical representation, if any
	 * @return Component's quantity as double
	 */
	double getQuantity();

	/**
	 * @brief Returns the Component's type
	 * @return Component's type as enumeration type ComponentType
	 */
	virtual ComponentType getType();

	/**
	 * @brief Checks if the given Component is a child of this Component
	 * @param child Component for which to check
	 * @retval true The given Component is a child of this Component
	 * @retval false The given Component is no child of this Component
	 */
	virtual bool hasChild( Component *child ) = 0;

	/**
	 * @brief Returns wether the Component is representing a vectorial expression
	 * @retval true The Component represents a vectorial expression
	 * @retval false The Component does not represent a vectorial expression
	 */
	virtual bool isVectorial() = 0;

	/**
	 * @brief Returns the Component's qualitative representation
	 * @return Component's quality as C++ string class
	 */
	virtual std::string getQuality() = 0;

	/**
	 * @brief Returns all Variables contained in this Component
	 * @param variables Pointer to C++ vector of Variables, containing all Variables on return
	 *
	 * Recursively checks all childs for their arguments being Variables. Pushes all found
	 * Variables into the vector.
	 */
	virtual void getVariables( std::vector<Variable*> *variables ) = 0;

	/**
	 * @brief Sets a numerical debug identification number
	 * @param dbgId Debug identification which shall be set
	 *
	 * Used for debug purposes only.
	 */
	virtual void setDebugId( int dbgId );

	/**
	 * @brief Returns the Component's debug ID
	 * @return Component's debug ID as integer
	 *
	 * Used for debug purposes only.
	 */
	virtual int getDebugId();

	/**
	 * @brief Replaces one Component in the whole Component-tree
	 * @param search Component which shall be replaced
	 * @param replace Component which shall replace the replaced one
	 *
	 * Recursively searches the given Component and replaces it with the other given Component
	 */
	virtual void replace( Component *search, Component *replace ) = 0;

	/**
	 * @brief Returns a clone of the Component
	 * @return The cloned Component
	 *
	 * Recursively clones the whole Component-tree and returns the new one
	 */
	virtual Component* clone() = 0;

	/**
	 * @brief Sets the object's members for the clone() method
	 * @param source Source Component from which the members shall be taken
	 * @param destination Destination Component in which the members shall be set
	 * @see clone()
	 */
	virtual void clone( Component *source, Component *destination );

	/**
	 * @brief Sets the Component's numerical representation
	 * @param quantity Value to set the Component's quantity to
	 */
	void setQuantity( double quantity );

protected:
	/**
	 * @brief The Component's numerical value, if any
	 */
	double quantity;

	/**
	 * @brief Identification number for debug purposes
	 */
	int debugId;

};

}


#endif /* COMPONENT_H_ */
