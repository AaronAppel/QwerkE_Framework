#ifndef _VertexData_H_
#define _VertexData_H_

#include "../../../../../QwerkE_Common/Math_Includes.h"


struct VertexData
{
	vec3 position;
	vec4 color;
	vec2 UV;
	vec3 normal;
	VertexData() {}
	VertexData(vec3 a_position, vec4 a_color, vec2 a_UV, vec3 a_normal)
	{
		position = a_position;
		color = a_color;
		UV = a_UV;
		normal = a_normal;
	}
};
#endif //!_VertexData_H_
