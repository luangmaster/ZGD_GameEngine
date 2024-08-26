#pragma once

namespace ZGD {

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1,
		DirectX = 2,
	};

	class Renderer {

	public:

		inline static RendererAPI GetAPI() { return m_RendererAPI; };

	private:
		static RendererAPI m_RendererAPI;
		
	};

}
