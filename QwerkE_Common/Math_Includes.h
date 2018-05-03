#ifndef _Math_Includes_H_
#define _Math_Includes_H_

// GLM
#include "Libraries/glm/glm/glm.hpp"
#include "Libraries/glm/glm/gtc/matrix_transform.hpp"
#include "Libraries/glm/glm//gtc/type_ptr.hpp"

#include <cmath>
#include "Libraries/Math/MathConstants.h"
#include "Libraries/Math/MathFunctions.h"
#include "Libraries/Math/MathHelpers.h"
#include "Libraries/Math/MathStuff.h"
#include "Libraries/Math/Vector.h"

/* Defines and typedefs */
// vector
typedef Vector2 vec2; // TODO: Put inside a file?
typedef Vector3 vec3;
typedef Vector4 vec4;

typedef Vector2Int ivec2;
typedef Vector3Int ivec3;
typedef Vector4Int ivec4;

#include "Libraries/Math/VectorMathHelpers.h"
#include "Libraries/Math/ValueChecking.h"
// quaternion
#include "Libraries/Math/MyQuaternion.h"
// matrix
#include "Libraries/Math/MyMatrix.h"
typedef MyMatrix mat4;

#endif // !_Math_Includes_H_
