#include "SiestaPlatformGLFW.h"

#include <GLFW/glfw3.h>

SPlatformGLFW::SPlatformGLFW()
{
	if (!glfwInit())
	{
		Debug::Critical("Failed to initialize GLFW");
	}

	Debug::Info("Platform GLFW initialized.");
}

SPlatformGLFW::~SPlatformGLFW()
{
	Debug::Info("Terminating platform GLFW");
	glfwTerminate();
}

IPlatformInterface* IPlatformInterface::Create()
{
	return new SPlatformGLFW();
}

IPlatformWindow* SPlatformGLFW::CreatePlatformWindow(int32 Width, int32 Height, TStringView Title)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* OutWindow = glfwCreateWindow(Width, Height, Title.data(), nullptr, nullptr);
	if (!m_FirstWindow)
	{
		m_FirstWindow = OutWindow;
	}

	if (!OutWindow)
	{
		Debug::Critical("Failed to create GLFW window.");
	}

	SWindowGLFW* Out = new SWindowGLFW;
	Out->m_Window = OutWindow;
	return Out;
}


bool SPlatformGLFW::ShouldExit() const
{
	return glfwWindowShouldClose(m_FirstWindow);
}

void SPlatformGLFW::Process()
{
	glfwPollEvents();
}

DWindowBounds SWindowGLFW::GetWindowBounds() const
{
	int32 Width, Height;
	glfwGetFramebufferSize(m_Window, &Width, &Height);
	return { Width, Height };
}

void* SWindowGLFW::GetNativeHandle() const
{
	return m_Window;
}

