#include "stdafx.h"
#include "CPartsManager.h"
#include "CPartsParser.h"


CPartsManager::CPartsManager()
{
}


CPartsManager::~CPartsManager()
{
}

void CPartsManager::GetPartsData(char* szFullPath)
{
	CPartsParser* pPartsParser = new CPartsParser;
	int size;	// 문서 크기
	char* doc = pPartsParser->ReadFile(szFullPath, &size);
	if (doc == NULL)
	{
		_DEBUG_COMMENT cout << "데이터 없음" << endl;
		return;
	}

	JSON partsJson;
	memset(&partsJson, 0, sizeof(JSON));
	pPartsParser->ParseJSON(doc, size, &partsJson);
	pPartsParser->SavePartsData(partsJson);
	pPartsParser->FreeJSON(&partsJson);
	free(doc);
	SafeDelete(pPartsParser);
}
