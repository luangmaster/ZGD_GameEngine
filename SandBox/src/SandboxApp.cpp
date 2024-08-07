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
		//ZGD_INFO("ExampleLayer::Update");

		if(ZGD::Input::IsKeyPressed(ZGD_KEY_TAB))
			ZGD_TRACE("Tab key is pressed (poll)!");
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