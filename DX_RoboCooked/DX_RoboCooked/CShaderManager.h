#pragma once
#include "CSingleton.h"

#define g_pShaderManager CShaderManager::GetInstance()

class CShaderManager : public CSingleton<CShaderManager>
{
	friend CSingleton<CShaderManager>;
	map<std::string, LPD3DXEFFECT> m_mapShader;
	//LPD3DXEFFECT m_pCurrentShader;
public:
	CShaderManager();
	~CShaderManager();

	LPD3DXEFFECT GetShader(char* szFullPath);
	LPD3DXEFFECT GetShader(string &sFullPath);
	void Destroy();
};

