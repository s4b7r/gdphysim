/*
 * kissms.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef KISSMS_H_
#define KISSMS_H_

// Include system libraries
#include <stdlib.h>
#include <vector>

// All parts of KissMS belong to the namespace kissms

namespace kissms {

/**
 * @brief ResultCode-Type for KissMS' methods
 */
enum ResultCode {
	Successful = 0,
	GeneralFailure,
	NotYetImplemented,
	NotCalculable,
	ImpossibleState
};
/** @var kissms::ResultCode kissms::Successful
 * @brief The method successfuly returned
 */
/** @var kissms::ResultCode kissms::GeneralFailure
 * @brief A general failure occured
 *
 * On return of GeneralFailure a general failure happend during
 * the method's execution. This may be any unespected error or an
 * error which does not match one of the following ResultCodes.
 *
 */
/** @var kissms::ResultCode kissms::NotYetImplemented
 * @brief The called method is not implemented
 *
 * The method which returns with NotYetImplemented is not capable
 * to do it's job due to a missing implementation. This method may
 * be developed currently or in the future.
 */
/** @var kissms::ResultCode kissms::NotCalculable
 * @brief
 *
 *
 */

// Forward declaration
class Variable;

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

// Include vectorial components
#include "kissms/component/vector/vector.h"
#include "kissms/component/vector/vectorproduct.h"


#endif /* KISSMS_H_ */
