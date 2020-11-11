#pragma once
#include "CScene.h"
class CGameScene :
	public CScene
{
public:
	CGameScene();
	~CGameScene();

	virtual void Init();
	virtual void Render();
	virtual void Update();
};

