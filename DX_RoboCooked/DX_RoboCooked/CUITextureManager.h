#pragma once
#define g_pUITextureManager CUITextureManager::GetInstance()

class CUITextureManager : public CSingleton<CUITextureManager>
{
private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
	std::map<std::string, D3DXIMAGE_INFO> m_mapTextureInFo;


public:
	CUITextureManager();
	~CUITextureManager();

public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string &szFullPath);
	
	D3DXIMAGE_INFO GetTextureInfo(char* szFullPath);
	D3DXIMAGE_INFO GetTextureInfo(std::string &szFullpath);

	D3DXVECTOR2 GetTextureSize(char* szFullPath);
	D3DXVECTOR2 GetTextureSize(std::string &szFullpath);

	
	void Destroy();	
};

