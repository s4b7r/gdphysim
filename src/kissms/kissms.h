/*
 * kissms.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef KISSMS_H_
#define KISSMS_H_

// XXX Recreate recursive procedures as iterative ones
// XXX Upgrade to modern C++ libraries

// Set debug flag to enable debug output
#define KISSMS_DEBUG_FLAG

// Set debug output macro
#ifdef KISSMS_DEBUG_FLAG
#define DP(x) std::cout << "DEBUG >> " << x << std::endl;
#else
#define DP(x)
#endif


// Include system libraries
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stack>
#include <sstream>
#include <queue>
#include <iostream>

// All parts of KissMS belong to the namespace kissms

/**
 * @brief KissMS-Namespace
 *
 * Namespace kissms contains the KissMS-Library
 * Keep it simple and stupid Math Solver
 */
namespace kissms {

/**
 * @brief ResultCode-Type for KissMS' methods
 */
enum ResultCode {
	Successful = 0,
	GeneralFailure,
	NotYetImplemented,
	NotCalculable,
	ImpossibleState,
	IsVectorial,
	DevelopersResult
};
/** @var kissms::ResultCode kissms::Successful
 * @brief The method successfuly returned
 */
/** @var kissms::ResultCode kissms::GeneralFailure
 * @brief A general failure occured
 *
 * On return of GeneralFailure a general failure happend during
 * the method's execution. This may be any unespected error or an
 * error which does not match one of the other ResultCodes.
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
 * @brief A calculation is not executeable
 *
 * A method which returned NotCalculable tried to calculate a
 * expression which contained an uncalculable Component
 */
/** @var kissms::ResultCode kissms::ImpossibleState
 * @brief The method reached an impossible state
 *
 * The method got to some point where it should be under no circumstances.
 */
/** @var kissms::ResultCode kissms::IsVectorial
 * @deprecated This result code is deprecated and will not be returned anywhere.
 */
/** @var kissms::ResultCode kissms::DevelopersResult
 * @brief Result code for developing reasons
 *
 * This result code is used by developers and should not occure in standard applications.
 */

/**
 * @brief Enumeration of all Component types
 */
enum ComponentType {
	tUnspecified = 0,
	tArgumentsOne,
	tArgumentsTwo,
	tEquation,
	tConstant,
	tVariable,
	tCosinus,
	tNegation,
	tReciprocal,
	tSinus,
	tAddition,
	tMultiplication,
	tVector,
	tVectorproduct,
	tSinusArc,
	tCosinusArc
};

// Forward declaration
class Variable;
class Equationsystem;

}

// Include abstract components
#include "kissms/component/component.h"
#include "kissms/component/argumentsOne.h"
#include "kissms/component/argumentsTwo.h"

// Include Equation and Equationsystem
#include "kissms/equation.h"
#include "kissms/equationsystem.h"

// Include scalar leaf components
#include "kissms/component/scalar-leaf/constant.h"
#include "kissms/component/scalar-leaf/variable.h"

// Include scalar components with one argument
#include "kissms/component/scalar-one/cosinus.h"
#include "kissms/component/scalar-one/negation.h"
#include "kissms/component/scalar-one/reciprocal.h"
#include "kissms/component/scalar-one/sinus.h"
#include "kissms/component/scalar-one/sinusarc.h"
#include "kissms/component/scalar-one/cosinusarc.h"

// Include scalar components with two arguments
#include "kissms/component/scalar-two/addition.h"
#include "kissms/component/scalar-two/multiplication.h"

// Include vectorial components
#include "kissms/component/vector/vector.h"
#include "kissms/component/vector/vectorproduct.h"


#endif /* KISSMS_H_ */
