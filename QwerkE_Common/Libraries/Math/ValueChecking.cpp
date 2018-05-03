#include "../../Math_Includes.h"

bool PointInBox(vec2 point, vec2 boxPosition, float width, float length)
{
	if (point.x > boxPosition.x - width * 0.5f &&
		point.x < boxPosition.x + width * 0.5f)
	{
		// within X bounds
		if (point.y > boxPosition.y - length * 0.5f &&
			point.y < boxPosition.y + length * 0.5f)
			// Within Y bounds
			return true;
	}
	return false;
}