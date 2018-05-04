#include "../../Graphics_Header.h"

std::string ShaderFactory::Basic3DShaderVert(std::string vertString)
{
	/* Header */
	AddAttributeVec3("Position", vertString);

	AddUniformMat4("WorldMat", vertString);
	AddUniformMat4("ViewMat", vertString);
	AddUniformMat4("ProjMat", vertString);

	/* Body */
	OpenMain(vertString);

	vertString.append("\ngl_Position = u_ProjMat * u_ViewMat * u_WorldMat * vec4(a_Position, 1.0);"); // open body

	CloseMain(vertString);

	return vertString;
}

std::string ShaderFactory::Basic3DShaderFrag(std::string fragString)
{
	/* Header */
	AddUniformVec4("ObjectColor", fragString);

	/* Body */
	OpenMain(fragString); // end header / begin body
	fragString.append("\ngl_FragColor = u_ObjectColor;");
	//
	CloseMain(fragString);

	return fragString;
}