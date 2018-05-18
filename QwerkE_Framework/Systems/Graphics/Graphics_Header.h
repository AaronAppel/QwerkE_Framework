#ifndef _Graphics_Header_H_
#define _Graphics_Header_H_

//////////////////////////////
// Graphics_Header.h
// #includes several graphics files for convenient includes
// in another file.
// TODO: Think of removing and only adding files that are needed.
//////////////////////////////
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
#include "ShaderProgram/ShaderProgram.h"
#include "ShaderProgram/ShaderFactory.h"

#include "Mesh/VertexData.h"
#include "Mesh/Mesh.h"
#include "Mesh/MeshFactory.h"
#include "Mesh/MeshUtilities.h"
#include "Mesh/Model.h"

#include "Gfx_Classes/Sprite.h"
#include "Gfx_Classes/CubeMap.h"
#include "Gfx_Classes/FrameBufferObject.h"
#include "Gfx_Classes/LightData.h"
#include "Gfx_Classes/Texture.h"

#include "GraphicsUtilities/GraphicsHelpers.h"

#endif // !_Graphics_Header_H_
