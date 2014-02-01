/*
 * kissms.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef KISSMS_H_
#define KISSMS_H_

// Include system libraries
#include <vector>

// All parts of KissMS belong to the namespace kissms

namespace kissms {

enum ResultCode {
	Successful = 0,
	Failure
};

// Forward declaration
// Currently there are no forward declarations

}

// Include abstract components
#include "kissms/component/component.h"
#include "kissms/component/argumentsOne.h"
#include "kissms/component/argumentsTwo.h"

// Include Equation
#include "kissms/equation.h"

// Include scalar leaf components
#include "kissms/component/scalar-leaf/constant.h"
#include "kissms/component/scalar-leaf/variable.h"

// Include scalar components with one argument
#include "kissms/component/scalar-one/cosinus.h"
#include "kissms/component/scalar-one/negation.h"
#include "kissms/component/scalar-one/reciprocal.h"
#include "kissms/component/scalar-one/sinus.h"

// Include scalar components with two arguments
#include "kissms/component/scalar-two/addition.h"
#include "kissms/component/scalar-two/multiplication.h"

// Include vectorial components with one argument
// TODO Does a vector belong to components with just one argument?
#include "kissms/component/vector-one/vector.h"

// Include vectorial components with two arguments
#include "kissms/component/vector-two/vectorproduct.h"


#endif /* KISSMS_H_ */
