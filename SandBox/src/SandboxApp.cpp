#include <ZGD.h>

class Sandbox : public ZGD::Application
{
public:
	Sandbox() {
	
	};
	~Sandbox() {
	
	};

private:

};

ZGD::Application* ZGD::CreateApplication()
{
	return new Sandbox();
}