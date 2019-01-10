#include "EditorPch.h"
#include "InspectorRendererFactory.h"
#include "Editor\Inspector\AnimationResourceInspector.h"
#include "Editor\Inspector\LevelResourceInspector.h"
#include "Editor\Inspector\UndefinedInspector.h"

namespace DerydocaEngine::Editor::Inspector
{
	
	InspectorRendererFactory::InspectorRendererFactory() :
		m_renderFunctions()
	{
		registerUndefinedRenderer(std::make_shared<UndefinedInspector>());
		registerRenderer<Resources::LevelResource>(std::make_shared<LevelResourceInspector>());
		registerRenderer<Resources::AnimationResource>(std::make_shared<AnimationResourceInspector>());
	}

	InspectorRendererFactory::~InspectorRendererFactory()
	{
	}

}
