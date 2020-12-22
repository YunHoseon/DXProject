#include "stdafx.h"
#include "CTextureManager.h"

static std::mutex cTextureMutex;

CTextureManager::CTextureManager(): CSingleton<CTextureManager>()
{
}

CTextureManager::~CTextureManager()
{
}

LPDIRECT3DTEXTURE9 CTextureManager::GetTexture(char* szFullPath)
{
	if(m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		cTextureMutex.lock();
		D3DXCreateTextureFromFileA(g_pD3DDevice, szFullPath, &m_mapTexture[szFullPath]);
		cTextureMutex.unlock();
	}
	if (m_mapTexture[szFullPath])
		m_mapTexture[szFullPath]->AddRef();
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 CTextureManager::GetTexture(string& sFullPath)
{
	if (m_mapTexture.find(sFullPath) == m_mapTexture.end())
	{
		cTextureMutex.lock();
		D3DXCreateTextureFromFileA(g_pD3DDevice, sFullPath.c_str(), &m_mapTexture[sFullPath]);
		cTextureMutex.unlock();
	}
	if (m_mapTexture[sFullPath])
		m_mapTexture[sFullPath]->AddRef();
	return m_mapTexture[sFullPath];
	
	//return GetTexture((char*)sFullPath.c_str());
}

void CTextureManager::Destroy()
{
	cTextureMutex.lock();
	for (auto & it : m_mapTexture)
	{
		SafeRelease(it.second);
	}
	m_mapTexture.clear();
	cTextureMutex.unlock();
}

