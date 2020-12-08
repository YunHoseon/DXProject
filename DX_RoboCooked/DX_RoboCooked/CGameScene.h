#pragma once
#include "CActor.h"
#include "CScene.h"
#include "IInteractCenter.h"
#include "CMonster.h"
class CField;
class CInteractiveActor;
class CParts;
class CCharacter;
class CUIButton;
class CBlueprint;
class CMonster;
class CTornado;


class CDebugPlayer1;
class CDebugPlayer2;

class CGameScene :
	public CScene, public IInteractCenter
{
private:
	CField*						m_pField;
	vector<CActor*>				m_vecStaticActor;
	vector<CInteractiveActor*>	m_vecObject;
	vector<CParts*>				m_vecParts;
	vector<CCharacter*>			m_vecCharacters;
	vector<CBlueprint*>			m_vecBlueprints;
	vector<CMonster*>			m_vecMonster;
	D3DXVECTOR3					m_vWind;
	CTornado*					m_pTornado;
	FLOAT						m_fGameTime;	
	BOOL						m_isTimeStop;
	INT							m_nLotIndex;



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
	void Load(string sFolder, string sFilename);

	void GetInteractObject(CCharacter* pCharacter) override;
	void AddParts(CParts* parts) override;
	void DeleteParts(CParts* parts) override;
	//void ThrowParts(CCharacter* pCharacter,CParts* parts,D3DXVECTOR3 vDir) override;
	void CheckAroundCombinator(CPartCombinator* combinator) override;
	//void SendPartsToOutlet(CParts* parts, COutlet* outlet) override;
	void ToggleStop() override;
	bool GetStop() override {return m_isTimeStop;}
	void MonsterSkill(eSkill skill) override;
	void FinishSkill(eSkill skill) override;
	bool CheckSpecificPartsID(string parts) override;
	float GetTime()override { return m_fGameTime; };
	void ElectIndexLot() override;
	bool CheckSpecificArea() override;



	CCrowdControl* ChooseCC(eSkill skill);
	void CC(CCrowdControl* pCC);
	void MedusaUlt();
	void SetWindDirection();
	void SetTornadoSkill();
	void DeleteWind();
	void DeleteTornado();
	void DeleteCC();
	bool IsGameClear();
	bool IsGameLose();
};

