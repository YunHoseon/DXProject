#pragma once
#include "CActor.h"
#include "CScene.h"

class CField;

class CGameScene :
	public CScene
{
private:
	CField*					m_pField;
	vector<CActor*>			m_vecStaticActor;
public:
	CGameScene();
	~CGameScene();

public:
	virtual void Init();
	virtual void Render();
	virtual void Update();
	
};

