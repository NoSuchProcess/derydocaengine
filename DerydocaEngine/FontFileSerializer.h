#pragma once
#include "FileTypeSerializer.h"

namespace DerydocaEngine::FileSerializers {

	class FontFileSerializer : public FileTypeSerializer
	{
	public:
		FontFileSerializer() {}
		~FontFileSerializer() {}

		YAML::Node generateResourceNodes(std::string const& filePath);
		FileType getFileType();
		Resources::Resource* loadResourceFromMeta(YAML::Node const& resourceNode);
	};

}
