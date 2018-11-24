#pragma once
#include "MaterialResourceSerializer.h"

namespace DerydocaEngine::Resources::Serializers
{

	class TextureResourceSerializer : public MaterialResourceSerializer
	{
	public:
		TextureResourceSerializer();
		~TextureResourceSerializer();

		void* deserialize(Resource* const& resource);
		ResourceType getResourceType();
	};

}