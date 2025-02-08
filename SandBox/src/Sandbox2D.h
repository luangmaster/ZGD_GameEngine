#pragma once

#include "ZGD.h"
#include "ParticleSystem.h"

class Sandbox2D : public ZGD::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(ZGD::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ZGD::Event& e) override;
private:
	ZGD::OrthographicCameraController m_CameraController;
	ZGD::Ref<ZGD::VertexArray> m_SquareVA;
	ZGD::Ref<ZGD::Shader> m_FlatColorShader;

	ZGD::Ref<ZGD::Texture2D> m_CheckerboardTexture;
	ZGD::Ref<ZGD::Texture2D> m_SpriteSheet;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};