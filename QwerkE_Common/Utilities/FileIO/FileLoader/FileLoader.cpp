#include "FileLoader.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Model/Model.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Model/Mesh/Mesh.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Model/Mesh/VertexData.h"
#include "../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Gfx_Classes/MaterialData.h"

namespace QwerkE
{
	namespace FileLoader
	{
		void LoadSound() // TODO:
		{
			// OpenAL?
		}

		void LoadImageFile() // TODO:
		{
			// determine image type and use proper library
			// lodepng, stb_image, SOIL, etc
		}
	}
}