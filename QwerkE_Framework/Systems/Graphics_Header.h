#ifndef _Graphics_Header_H_
#define _Graphics_Header_H_

/* Ensures graphics classes are included in order */

// defines, structs, typedefs for graphics
#define Wind_CCW 0
// TODO: Move enum to maybe ShaderFactory or somewhere
// that does not include a lot of other code. This is
// to avoid including more that necessary else where.
enum eShaderTypes
{
	eShader_Basic2D = 0,
	eShader_Basic3D,
	eShader_LitMaterial
};
// my graphics classes
#include "Graphics/ShaderProgram/ShaderProgram.h"
#include "Graphics/ShaderProgram/ShaderFactory.h"

#include "Graphics/Model/Mesh/VertexData.h"
#include "Graphics/Model/Mesh/Mesh.h"
#include "Graphics/Model/Mesh/MeshFactory.h"
#include "Graphics/Model/Mesh/MeshUtilities.h"

#include "Graphics/Sprite/Sprite.h"

#include "Graphics/CubeMap/CubeMap.h"
#include "Graphics/FBO/FrameBufferObject.h"
#include "Graphics/Model/Model.h"

#endif // !_Graphics_Header_H_
