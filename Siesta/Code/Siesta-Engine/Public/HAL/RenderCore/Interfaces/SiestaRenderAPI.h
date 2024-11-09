#pragma once

#include "SiestaCore.h"

#ifdef WIN32
#define DEFAULT_RENDER_API "SD3D12RenderAPI"
#define DEFAULT_RENDER_API_MODULE "RenderD3D12"
#else
#error "Unsupported platform"
#endif

class SRenderDevice;
class SWindowRenderState;
class IPlatformWindow;
class SRenderContext;

class SRenderAPI
{
	static SRenderAPI* Instance;
public:
	SRenderAPI();

	virtual ~SRenderAPI();

	static SRenderAPI* Get();

	template<typename T>
	static T* Get()
	{
		return static_cast<T*>(Get());
	}

	inline SRenderDevice* GetDevice() const { return m_RenderDevice; }
	PSharedPtr<SWindowRenderState> CreateWindowRenderState(const IPlatformWindow* Window);

	template<typename T>
	inline T* GetDevice() const { return static_cast<T*>(m_RenderDevice); }

	SRenderContext* GetRenderContext();

	void SubmitDeviceWorkHelper();

	virtual void OnFrameFinished() = 0;

private:
	SModule* m_LoadedModule{};

protected:
	SRenderDevice* m_RenderDevice{};
	SRenderContext* m_RenderContext{};

	virtual void InitRenderContext_Impl() {}
};

extern SRenderAPI* HALCreateRenderAPI();