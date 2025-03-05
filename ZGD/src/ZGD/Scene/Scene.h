#pragma once

#include "entt.hpp"

#include "ZGD/Core/TimeStep.h"

namespace ZGD {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}