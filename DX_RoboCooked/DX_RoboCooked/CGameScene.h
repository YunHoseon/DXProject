#pragma once
#include "CActor.h"
#include "CScene.h"
#include "IInteractCenter.h"
class CField;
class CInteractiveActor;
class CParts;
class CCharacter;

/* µð¹ö±ë¿ë */
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

	/* µð¹ö±ë¿ë */
	CDebugPlayer1*				m_pDebugSphere;
	CDebugPlayer2*				m_pDebugCube;
	CParts*						m_pDebugParts;
public:
	CGameScene();
	~CGameScene();

public:
	virtual void Init();
	virtual void Render();
	virtual void Update();
	void GetInteractObject(CCharacter* pCharacter) override;
	void AddParts(CParts* parts) override;
	void DownParts(CParts* parts,D3DXVECTOR3 vDir) override;
	void CheckAroundCombinator(CPartCombinator* combinator) override;
};

