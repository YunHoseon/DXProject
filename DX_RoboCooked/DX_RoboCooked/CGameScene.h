#pragma once
#include "CScene.h"

class CField;

class CGameScene :
	public CScene
{
private:
	CField* m_pField;
public:
	CGameScene();
	~CGameScene();

public:
	virtual void Init();
	virtual void Render();
	virtual void Update();
	
};

