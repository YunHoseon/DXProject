#pragma once
#include "CActor.h"
#include "CScene.h"
#include "IInteractCenter.h"
class CField;
class CInteractiveActor;
class CParts;
class CCharacter;
class CUIButton;

/* ������ */
class CDebugPlayer1;
class CDebugPlayer2;

class CGameScene :
	public CScene, public IInteractCenter
{
private:
	CField*						m_pField;
	vector<CActor*>				m_vecStaticActor;
	vector<CInteractiveActor*>	m_vecObject;
	vector<CInteractiveActor*>	m_vecParts;
	vector<CCharacter*>			m_vecCharacters;

	bool						m_isTimeStop;
	/* ������ */
	CDebugPlayer1*				m_pDebugSphere;
	CDebugPlayer2*				m_pDebugCube;
	CParts*						m_pDebugParts;
	CUIButton*					m_pDebugPauseUI;

public:
	CGameScene();
	virtual ~CGameScene();

public:
	virtual void Init();
	virtual void Render();
	virtual void Update();

	void GetInteractObject(CCharacter* pCharacter) override;
	void AddParts(CParts* parts) override;
	void DeleteParts(CParts* parts) override;
	//void ThrowParts(CCharacter* pCharacter,CParts* parts,D3DXVECTOR3 vDir) override;
	void CheckAroundCombinator(CPartCombinator* combinator) override;
	//void SendPartsToOutlet(CParts* parts, COutlet* outlet) override;
	void ToggleStop() override;
	bool GetStop() override {return m_isTimeStop;}

};

