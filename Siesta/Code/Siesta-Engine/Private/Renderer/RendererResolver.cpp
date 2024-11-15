#include "RendererResolver.h"

#include "SceneRenderer.h"

SRenderer* SRendererResolver::GetOrCreate(ERendererType Type)
{
	switch (Type)
	{
		case ERendererType::Scene:
		{
			if (m_SceneRenderer)
				return m_SceneRenderer;

			m_SceneRenderer = new SSceneRenderer();
			return m_SceneRenderer;
		}
		default:
			Debug::Critical("Unhandled renderer type.");
			break;
	}

	return nullptr;
}

SRenderer* SRendererResolver::m_SceneRenderer;

void SRendererResolver::Terminate()
{
	if (m_SceneRenderer)
	{
		delete m_SceneRenderer;
	}
}

