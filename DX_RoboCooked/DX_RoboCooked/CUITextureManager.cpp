#include "stdafx.h"
#include "CUITextureManager.h"


CUITextureManager::CUITextureManager() : CSingleton<CUITextureManager>()
{
}

CUITextureManager::~CUITextureManager()
{
}

LPDIRECT3DTEXTURE9 CUITextureManager::GetTexture(char* szFullPath)
{
	if (szFullPath == NULL)
		return NULL;
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileExA(
			g_pD3DDevice,
			szFullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapTextureInFo[szFullPath],
			NULL,
			&m_mapTexture[szFullPath]
		);
	}
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 CUITextureManager::GetTexture(std::string& szFullPath)
{
	return GetTexture((char*)szFullPath.c_str());
}

D3DXIMAGE_INFO CUITextureManager::GetTextureInfo(char* szFullPath)
{
	if (m_mapTextureInFo.find(szFullPath) == m_mapTextureInFo.end())
	{
		D3DXCreateTextureFromFileExA(
			g_pD3DDevice,
			szFullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapTextureInFo[szFullPath],
			NULL,
			&m_mapTexture[szFullPath]
		);
	}
	return m_mapTextureInFo[szFullPath];
}

D3DXIMAGE_INFO CUITextureManager::GetTextureInfo(std::string& szFullpath)
{
	return GetTextureInfo((char*)szFullpath.c_str());
}

D3DXVECTOR2 CUITextureManager::GetTextureSize(char* szFullPath)
{
	D3DXVECTOR2 vTemp(0,0);
	if (m_mapTextureInFo.find(szFullPath) == m_mapTextureInFo.end())
	{
		GetTextureInfo(szFullPath);
	}
	vTemp.x = m_mapTextureInFo[szFullPath].Width;
	vTemp.y = m_mapTextureInFo[szFullPath].Height;
	


	return vTemp;
}

D3DXVECTOR2 CUITextureManager::GetTextureSize(std::string& szFullpath)
{
	return GetTextureSize((char*)szFullpath.c_str());
}

void CUITextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SafeRelease(it.second);
	}
	m_mapTexture.clear();
}
