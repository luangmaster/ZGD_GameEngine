#pragma once

#ifdef ZGD_PLATFORM_WINDOWS

extern ZGD::Application* ZGD::CreateApplication();

int main(int argc, char** argv)
{
	ZGD::Log::Init();

	ZGD_PROFILE_BEGIN_SESSION("Startup", "ZGDProfile-Start.json");
	auto app = ZGD::CreateApplication();
	ZGD_PROFILE_END_SESSION();

	ZGD_PROFILE_BEGIN_SESSION("Runtime", "ZGDProfile-Runtime.json");
	app->Run();
	ZGD_PROFILE_END_SESSION();

	ZGD_PROFILE_BEGIN_SESSION("Shutdown", "ZGDProfile-Shutdown.json");
	delete app;
	ZGD_PROFILE_END_SESSION();
}


#endif
