﻿#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MapWidth = 24; 
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWDDDDDDWWWWWWWWWWW"
"WWWWWDDDDDDDDDDDWWWWWWWW"
"WWWWDDDDDDDDDDDDDCDWWWWW"
"WWWDDDDDDDDDDDDDDDDDDWWW"
"WWDDDDWWWDDDDDDDDDDDDWWW"
"WDDDDDWWWDDDDDDDDDDDDDWW"
"WWDDDDDDDDDDDDDDDDDDDWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWWWWDDDDDDDDDDDWWWWWWW"
"WWWWWWWDDDDDDDDDWWWWWWWW"
"WWWWWWWWWWDDDDWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	ZGD_PROFILE_FUNCTION();

	m_CheckerboardTexture = ZGD::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = ZGD::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");
	m_TextureStairs = ZGD::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, {128, 128});
	m_TextureBarrel = ZGD::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8, 2 }, {128, 128 });
	m_TextureTree = ZGD::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

	s_TextureMap['D'] = ZGD::SubTexture2D::CreateFromCoords(m_SpriteSheet, {6, 11}, {128, 128});
	s_TextureMap['W'] = ZGD::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach()
{
	ZGD_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(ZGD::TimeStep ts)
{
	ZGD_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);
	

	// Render
	ZGD::Renderer2D::ResetStats();
	{
		ZGD_PROFILE_SCOPE("Renderer Prep");
		ZGD::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZGD::RenderCommand::Clear();
	}

#if 0
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		ZGD_PROFILE_SCOPE("Renderer Draw");
		ZGD::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ZGD::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -30.0f, { 0.8f, 0.2f, 0.3f, 1.0f });   //红
		//ZGD::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		ZGD::Renderer2D::DrawQuad({ 0.5f , -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f }); //蓝
		ZGD::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		//ZGD::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, rotation, m_CheckerboardTexture, 2.0f);
		ZGD::Renderer2D::EndScene();

		ZGD::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				ZGD::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		ZGD::Renderer2D::EndScene();
	}
#endif

	if (ZGD::Input::IsMouseButtonPressed(ZGD_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = ZGD::Input::GetMousePosition();
		auto width = ZGD::Application::Get().GetWindow().GetWidth();
		auto height = ZGD::Application::Get().GetWindow().GetHeight();
		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPostion();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	ZGD::Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];
			ZGD::Ref<ZGD::SubTexture2D> texture;
			if (s_TextureMap.find(tileType) != s_TextureMap.end())
				texture = s_TextureMap[tileType];
			else
				texture = m_TextureStairs;

			ZGD::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
		}
	}


	//ZGD::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureStairs);
	//ZGD::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureBarrel);
	//ZGD::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.5f }, { 1.0f, 2.0f }, m_TextureTree);
	ZGD::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{

	ZGD_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = ZGD::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(ZGD::Event& e)
{
	m_CameraController.OnEvent(e);
}
