#pragma once

#include "HAL/Platform.h"

struct GLFWwindow;

class SWindowGLFW : public IPlatformWindow
{
public:
	virtual void* GetNativeHandle() const override;
	virtual Math::XMINT2 GetWindowSize() const override;

private:
	GLFWwindow* m_Window{};
	friend class SPlatformGLFW;
};

class SPlatformGLFW : public IPlatform
{
public:
	SPlatformGLFW();
	~SPlatformGLFW();

	virtual IPlatformWindow* CreatePlatformWindow(int32 Width, int32 Height, TStringView Title) override;
	virtual bool ShouldExit() const override;
	virtual void Process() override;

	virtual IPlatformWindow* GetMainWindow() const override;

private:
	GLFWwindow* m_FirstWindow{};
};