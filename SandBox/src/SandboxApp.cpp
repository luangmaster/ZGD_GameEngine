#include <ZGD.h>

class ExampleLayer : public ZGD::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		ZGD_INFO("ExampleLayer::Update");
	}

	void OnEvent(ZGD::Event& event) override
	{
		ZGD_TRACE("{0}", event);
	}

};

class Sandbox : public ZGD::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new ZGD::ImGuiLayer());
	}
	~Sandbox() {
	
	}

private:

};

ZGD::Application* ZGD::CreateApplication()
{
	return new Sandbox();
}