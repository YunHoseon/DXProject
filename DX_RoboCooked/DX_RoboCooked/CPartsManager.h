#pragma once

#define g_pPartsManager CPartsManager::GetInstance()

class CPartsParser;
class CPartsManager : public CSingleton<CPartsManager>
{
public:
	CPartsManager();
	~CPartsManager();

	void GetPartsData(char* szFullPath);
};

