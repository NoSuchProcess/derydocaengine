#include "EditorComponentsPch.h"
#include "EngineAssetBrowser.h"
#include "ObjectLibrary.h"
#include "Scenes\SceneManager.h"

namespace DerydocaEngine::Components
{

	EngineAssetBrowser::EngineAssetBrowser()
	{
		m_selectionGroup = Editor::SelectionManager::getInstance().getPrimarySelectionGroup();
	}

	EngineAssetBrowser::~EngineAssetBrowser()
	{
	}

	void EngineAssetBrowser::renderWindow()
	{
		if (m_resourceNode.expired())
		{
			m_resourceNode = ObjectLibrary::getInstance().getRootResourceTreeNode();
			return;
		}

		auto root = m_resourceNode.lock();

		ImGui::ShowDemoWindow();

		renderNodeContent(root);
	}

	void EngineAssetBrowser::renderNodeContent(std::shared_ptr<Resources::ResourceTreeNode> node)
	{
		for (auto child : node->getChildren())
		{
			renderNode(child);
		}

		for (auto resource : node->getResources())
		{
			renderResourceNode(resource);
		}
	}

	void EngineAssetBrowser::renderNode(std::shared_ptr<Resources::ResourceTreeNode> node)
	{
		if (ImGui::TreeNode(node->getName().c_str()))
		{
			renderNodeContent(node);

			ImGui::TreePop();
		}
	}

	void EngineAssetBrowser::renderResourceNode(std::shared_ptr<Resources::Resource> resource)
	{
		std::string id = boost::uuids::to_string(resource->getId());
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		if (m_selectionGroup->isSelected(resource))
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}
		ImGui::TreeNodeEx(id.c_str(), flags, "%s", resource->getName().c_str());
		if (ImGui::IsItemClicked())
		{
			m_selectionGroup->select(resource);
		}
	}

}
