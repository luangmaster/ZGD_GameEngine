#include <ZGD.h>
#include "imgui/imgui.h"

class ExampleLayer : public ZGD::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(ZGD::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f,  0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
		};
		std::shared_ptr<ZGD::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ZGD::VertexBuffer::Create(vertices, sizeof(vertices)));

		ZGD::BufferLayout layout = {
			{ZGD::ShaderDataType::Float3, "a_Position"},
			{ZGD::ShaderDataType::Float4, "a_Color"},
			//{ShaderDataType::Float3, "a_Normal"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<ZGD::IndexBuffer> indexBuffer;
		indexBuffer.reset(ZGD::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// 再创建一个渲染正方形的vertexArray
		m_SquareVA.reset(ZGD::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<ZGD::VertexBuffer> squareVB;
		squareVB.reset(ZGD::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ZGD::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<ZGD::IndexBuffer> squareIB;
		squareIB.reset(ZGD::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position+0.5;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position, 1.0);
				color = v_Color;
			}

		)";

		m_Shader.reset(new ZGD::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new ZGD::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (ZGD::Input::IsKeyPressed(ZGD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (ZGD::Input::IsKeyPressed(ZGD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (ZGD::Input::IsKeyPressed(ZGD_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (ZGD::Input::IsKeyPressed(ZGD_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (ZGD::Input::IsKeyPressed(ZGD_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (ZGD::Input::IsKeyPressed(ZGD_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		ZGD::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZGD::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ZGD::Renderer::BeginScene(m_Camera);

		ZGD::Renderer::Submit(m_BlueShader, m_SquareVA);
		ZGD::Renderer::Submit(m_Shader, m_VertexArray);

		ZGD::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(ZGD::Event& event) override
	{
		/*	ZGD_TRACE("{0}", event);*/
		if (event.GetEventType() == ZGD::EventType::KeyPressed) {
			ZGD::KeyPressedEvent& e = (ZGD::KeyPressedEvent&)event;
			if (e.GetKeyCode() == ZGD_KEY_TAB)
				ZGD_TRACE("Tab key is pressed (event)!");
			ZGD_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

private:
	std::shared_ptr<ZGD::Shader> m_Shader;
	std::shared_ptr<ZGD::VertexArray> m_VertexArray;

	std::shared_ptr<ZGD::Shader> m_BlueShader;
	std::shared_ptr<ZGD::VertexArray> m_SquareVA;

	ZGD::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.05f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.1f;
};

class Sandbox : public ZGD::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {
	
	}

private:

};

ZGD::Application* ZGD::CreateApplication()
{
	return new Sandbox();
}