#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = ZGD::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(ZGD::TimeStep ts)
{
	ZGD_PROFILE_FUNCTION();

	// Update
	{
		ZGD_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	

	// Render
	{
		ZGD_PROFILE_SCOPE("Renderer Prep");
		ZGD::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZGD::RenderCommand::Clear();
	}

	{
		ZGD_PROFILE_SCOPE("Renderer Draw");
		ZGD::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ZGD::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f}, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });   //ºì
		ZGD::Renderer2D::DrawQuad({ 0.0f, -0.5f , -0.1f}, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f }); //À¶
		ZGD::Renderer2D::DrawQuad({ 0.5f, 0.0f, -0.2f }, { 5.0f, 5.0f }, m_CheckerboardTexture);
		ZGD::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{

	ZGD_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(ZGD::Event& e)
{
	m_CameraController.OnEvent(e);
}
