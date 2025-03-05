#include "zgdpch.h"
#include "Entity.h"

namespace ZGD {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}
}