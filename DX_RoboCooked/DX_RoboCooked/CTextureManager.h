#pragma once

//class CTextureManager;
#define g_pTextureManager CTextureManager::GetInstance()
class CTextureManager : public CSingleton<CTextureManager>
{
private:
	
	std::map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
	friend CSingleton<CTextureManager>;
	CTextureManager();
	~CTextureManager();
public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(string &sFullPath);
	void Destroy();
};
