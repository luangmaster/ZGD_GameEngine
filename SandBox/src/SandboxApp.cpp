#include <ZGD.h>
#include <ZGD/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public ZGD::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray = ZGD::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f,  0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
		};
		ZGD::Ref<ZGD::VertexBuffer> vertexBuffer = ZGD::VertexBuffer::Create(vertices, sizeof(vertices));

		ZGD::BufferLayout layout = {
			{ZGD::ShaderDataType::Float3, "a_Position"},
			{ZGD::ShaderDataType::Float4, "a_Color"},
			//{ShaderDataType::Float3, "a_Normal"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		ZGD::Ref<ZGD::IndexBuffer> indexBuffer = ZGD::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// 再创建一个渲染正方形的vertexArray
		m_SquareVA = ZGD::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		ZGD::Ref<ZGD::VertexBuffer> squareVB = ZGD::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ZGD::ShaderDataType::Float3, "a_Position" },
			{ ZGD::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ZGD::Ref<ZGD::IndexBuffer> squareIB = ZGD::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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

		m_Shader = ZGD::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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
		m_FlatColorShader = ZGD::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";
		m_TextureShader = ZGD::Shader::Create("assets/shaders/Texture.glsl");
		m_Texture = ZGD::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = ZGD::Texture2D::Create("assets/textures/ChernoLogo.png");
		std::dynamic_pointer_cast<ZGD::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<ZGD::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(ZGD::TimeStep ts) override
	{
		ZGD_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds());

		m_CameraController.OnUpdate(ts);

		ZGD::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZGD::RenderCommand::Clear();

		ZGD::Renderer::BeginScene(m_CameraController.GetCamera());

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

		//ZGD::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		//glm::mat4 scale1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition) * scale1;
		// Triangle
		//ZGD::Renderer::Submit(m_Shader, m_VertexArray, transform);
		m_Texture->Bind();
		ZGD::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		ZGD::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
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
		m_CameraController.OnEvent(event);
	}

private:
	ZGD::Ref<ZGD::Shader> m_Shader;
	ZGD::Ref<ZGD::VertexArray> m_VertexArray;

	ZGD::Ref<ZGD::Shader> m_FlatColorShader,m_TextureShader;
	ZGD::Ref<ZGD::VertexArray> m_SquareVA;
	ZGD::Ref<ZGD::Texture2D> m_Texture, m_ChernoLogoTexture;

	ZGD::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_SquareMoveSpeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	glm::vec3 m_SquarePosition;
};

class Sandbox : public ZGD::Application
{
public:
	Sandbox() {
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {
	
	}

private:

};

ZGD::Application* ZGD::CreateApplication()
{
	return new Sandbox();
}