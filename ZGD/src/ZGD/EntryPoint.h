#pragma once

#ifdef ZGD_PLATFORM_WINDOWS

extern ZGD::Application* ZGD::CreateApplication();

int main(int argc, char** argv)
{
	ZGD::Log::Init();
	ZGD_CORE_WARN("Initialized Log!");
	int a = 5;
	ZGD_INFO("Var a = {0}", a);

	auto app = ZGD::CreateApplication();
	app->Run();
	delete app;
}


#endif
