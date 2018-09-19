#include "ImageFileSerializer.h"
#include "Resource.h"

namespace DerydocaEngine::FileSerializers {

	YAML::Node ImageFileSerializer::generateResourceNodes(std::string const& filePath)
	{
		YAML::Node resources;

		YAML::Node materialResource;
		materialResource["ID"] = generateUuid();

		resources.push_back(materialResource);

		return resources;
	}

	FileType ImageFileSerializer::getFileType()
	{
		return FileType::ImageFileType;
	}

	Resources::Resource * ImageFileSerializer::loadResourceFromMeta(YAML::Node const& resourceNode)
	{
		// Create a material resource type
		Resources::Resource* r = new Resources::Resource();
		r->setType(Resources::TextureResourceType);
		return r;
	}

}
