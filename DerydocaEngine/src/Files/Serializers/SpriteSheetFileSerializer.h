#pragma once
#include "Files\Serializers\FileTypeSerializer.h"

namespace DerydocaEngine::Files::Serializers {

	class SpriteSheetFileSerializer : public FileTypeSerializer
	{
	public:
		SpriteSheetFileSerializer() {}
		~SpriteSheetFileSerializer() {}

		YAML::Node generateResourceNodes(std::string const& filePath);
		Files::FileType getFileType();
		std::shared_ptr<Resources::Resource> loadResourceFromMeta(YAML::Node const& resourceNode);
	};

}
