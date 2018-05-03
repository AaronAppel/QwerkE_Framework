#ifndef _VectorMathHelpers_H_
#define _VectorMathHelpers_H_

#include "../../Math_Includes.h"

static float CalculateDistance2D(Vector2 a_TipPosition, Vector2 a_TailPosition);
static float CalculateDistance3D(Vector3 a_TipPosition, Vector3 a_TailPosition);
static float CalculateDistance3DXZ(Vector3 a_TipPosition, Vector3 a_TailPosition);
static float CalculateDistance3DXY(Vector3 a_TipPosition, Vector3 a_TailPosition);
static float CalculateAngleXZ(Vector3 a_TipPosition, Vector3 a_TailPosition);

#endif // !_VectorMathHelpers_H_