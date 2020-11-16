#pragma once
#include "CActor.h"
#include "CScene.h"

class CField;
class CInteractiveActor;

class CGameScene :
	public CScene,CEventListener
{
private:
	CField*						m_pField;
	vector<CActor*>				m_vecStaticActor;
	vector<CInteractiveActor*>	m_vecObject;
	vector<CInteractiveActor*>	m_vecParts;
public:
	CGameScene();
	~CGameScene();

public:
	virtual void Init();
	virtual void Render();
	virtual void Update();
	void OnEvent(EEvent eEvent, void* _value) override;
};

