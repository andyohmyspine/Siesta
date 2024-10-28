#pragma once

#include "Interfaces/IPlatform.h"
#include "Interfaces/IPlatformWindow.h"

extern "C" typedef struct GLFWwindow GLFWwindow;

class SWindowGLFW : public IPlatformWindow
{
public:
	virtual void* GetNativeHandle() const override;
	virtual Math::XMINT2 GetWindowSize() const override;

private:
	GLFWwindow* m_Window{};
	friend class SPlatformGLFW;
};

class SPlatformGLFW : public IPlatformInterface
{
public:
	SPlatformGLFW();
	~SPlatformGLFW();

	virtual IPlatformWindow* CreatePlatformWindow(int32 Width, int32 Height, TStringView Title) override;
	virtual bool ShouldExit() const override;
	virtual void Process() override;

private:
	GLFWwindow* m_FirstWindow{};
};