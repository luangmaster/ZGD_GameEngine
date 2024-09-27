#include <ZGD.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public ZGD::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(ZGD::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f,  0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
		};
		ZGD::Ref<ZGD::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ZGD::VertexBuffer::Create(vertices, sizeof(vertices)));

		ZGD::BufferLayout layout = {
			{ZGD::ShaderDataType::Float3, "a_Position"},
			{ZGD::ShaderDataType::Float4, "a_Color"},
			//{ShaderDataType::Float3, "a_Normal"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		ZGD::Ref<ZGD::IndexBuffer> indexBuffer;
		indexBuffer.reset(ZGD::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// 再创建一个渲染正方形的vertexArray
		m_SquareVA.reset(ZGD::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		ZGD::Ref<ZGD::VertexBuffer> squareVB;
		squareVB.reset(ZGD::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ZGD::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ZGD::Ref<ZGD::IndexBuffer> squareIB;
		squareIB.reset(ZGD::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader.reset(ZGD::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";
		m_FlatColorShader.reset(ZGD::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(ZGD::TimeStep ts) override
	{
		ZGD_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds());

		if (ZGD::Input::IsKeyPressed(ZGD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (ZGD::Input::IsKeyPressed(ZGD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (ZGD::Input::IsKeyPressed(ZGD_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (ZGD::Input::IsKeyPressed(ZGD_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (ZGD::Input::IsKeyPressed(ZGD_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (ZGD::Input::IsKeyPressed(ZGD_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (ZGD::Input::IsKeyPressed(ZGD_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (ZGD::Input::IsKeyPressed(ZGD_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;

		if (ZGD::Input::IsKeyPressed(ZGD_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (ZGD::Input::IsKeyPressed(ZGD_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		ZGD::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZGD::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ZGD::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		std::dynamic_pointer_cast<ZGD::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ZGD::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 25; x++)
			{
				glm::vec3 pos(x * 0.11f-1.3, y * 0.11f-0.75, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				ZGD::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		glm::mat4 scale1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition) * scale1;

		ZGD::Renderer::Submit(m_Shader, m_VertexArray, transform);

		ZGD::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
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
	ZGD::Ref<ZGD::Shader> m_Shader;
	ZGD::Ref<ZGD::VertexArray> m_VertexArray;

	ZGD::Ref<ZGD::Shader> m_FlatColorShader;
	ZGD::Ref<ZGD::VertexArray> m_SquareVA;

	ZGD::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_SquareMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	glm::vec3 m_SquarePosition;
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