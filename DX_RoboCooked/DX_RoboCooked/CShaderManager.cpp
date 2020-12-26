#include "stdafx.h"
#include "CShaderManager.h"


CShaderManager::CShaderManager()
{
}


CShaderManager::~CShaderManager()
{
	//Destroy();
}

LPD3DXEFFECT CShaderManager::GetShader(char * szFullPath)
{
	if (m_mapShader.find(szFullPath) == m_mapShader.end())
	{
		DWORD dwShaderFlags = 0;
#if _DEBUG
		dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

		D3DXCreateEffectFromFileA(g_pD3DDevice, szFullPath,
			NULL, NULL, dwShaderFlags, NULL, &m_mapShader[szFullPath], NULL);
	}
	m_mapShader[szFullPath]->AddRef();
	return m_mapShader[szFullPath];
}

void CShaderManager::Destroy()
{
	for (auto & it : m_mapShader)
	{
		SafeRelease(it.second);
	}
	m_mapShader.clear();
}
