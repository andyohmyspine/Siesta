#pragma once

#include "Core.h"

class SRenderer;
enum class ERendererType : uint8;

class SRendererResolver
{
public:
	static SRenderer* GetOrCreate(ERendererType Type);
	static void Terminate();

private:
	static SRenderer* m_SceneRenderer;
};