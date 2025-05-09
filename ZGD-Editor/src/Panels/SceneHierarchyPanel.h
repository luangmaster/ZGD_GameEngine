#pragma once

//#include "ZGD/Core/Base.h"
#include "ZGD/Core/Log.h"
#include "ZGD/Scene/Scene.h"
#include "ZGD/Scene/Entity.h"

namespace ZGD {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}