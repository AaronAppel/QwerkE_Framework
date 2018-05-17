#include "FileLoader.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Model.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Mesh.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/VertexData.h"
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

		Material* GetMaterialFromMatFile(const char* path)
		{
			// TODO:
			assert(false); // Don't use!
			return nullptr;
		}
	}
}