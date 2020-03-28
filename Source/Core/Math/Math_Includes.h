#ifndef _Math_Includes_H_
#define _Math_Includes_H_

#include "MathConstants.h"
#include "MathFunctions.h"
#include "MathHelpers.h"
#include "MathStuff.h"
#include "VectorMathHelpers.h"
#include "ValueChecking.h"
// quaternion
#include "MyQuaternion.h"
// matrix
#pragma warning( disable : 26495 )
#include "MyMatrix.h"
#pragma warning( default : 26495 )
typedef MyMatrix mat4;

#endif // !_Math_Includes_H_
