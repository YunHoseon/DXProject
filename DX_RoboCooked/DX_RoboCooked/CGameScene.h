#pragma once
#include "CActor.h"
#include "CScene.h"
#include "IInteractCenter.h"
#include "CEventListener.h"
#include "CMonster.h"

class CTile;
class CField;
class CInteractiveActor;
class CParts;
class CCharacter;
class CUIButton;
class CUIWarning;
class CBlueprint;
class CMonster;
class CTornado;
class CUITrafficLight;
class CUILoading;
class CUIReady;

class CDebugPlayer1;
class CDebugPlayer2;

class CGameScene : public CScene, public IInteractCenter, public CEventListener
{
private:
	vector<CActor*>				m_vecStaticActor;
	vector<CTile*>				m_vecTile;
	vector<CInteractiveActor*>	m_vecObject;
	vector<CParts*>				m_vecParts;
	vector<CCharacter*>			m_vecCharacters;
	vector<CBlueprint*>			m_vecBlueprints;
	vector<CMonster*>			m_vecMonster;

	D3DXVECTOR3 m_vWind;
	FLOAT m_fGameTime;
	BOOL m_isTimeStop;

	CUIButton *m_pDebugLoseUI;
	CUIButton *m_pDebugClearUI;
	CUIButton *m_pDebugPauseUI;
	CUIButton *m_pEscUI;
	CUITrafficLight *m_pDebugTrafficLight;
	CUILoading *m_pLoadingPopup;
	CUIButton *m_pReady;
	CUIWarning *m_pWarnning;

	static std::mutex m_cMutex;
	string m_sStageKey;

public:
	CGameScene();
	virtual ~CGameScene();

public:
	virtual void Init();
	virtual void Render();
	virtual void Update();

	bool OnEvent(eEvent eEvent, void *_value) override;
	bool TickUpdate(void *_value);

	void Load(string sFolder, string sStageKey, void (CGameScene::*pCallback)() = nullptr);
	void AddParts(CParts *parts) override;
	void DeleteParts(CParts *parts) override;
	//void ThrowParts(CCharacter* pCharacter,CParts* parts,D3DXVECTOR3 vDir) override;
	void CheckAroundCombinator(CPartCombinator *combinator) override;
	//void SendPartsToOutlet(CParts* parts, COutlet* outlet) override;
	void ToggleStop() override;

	void GetInteractObject(CCharacter *pCharacter) override;
	void ApplyMonsterSkill(eSkill skill, float fDuration = 0) override;
	void FinishSkill(eSkill skill) override;
	bool CheckSpecificPartsID(string parts) override;
	D3DXVECTOR3 SelectRandomObject() override;
	bool CheckDistanceToSelectedObject(D3DXVECTOR3 pos, float fSize) override;
	void CheckCollideCharacterToSandpile(ICollisionArea *collision) override;
	void DestroyPartsOnPosition(D3DXVECTOR3 pos) override;
	bool CheckWarning() override;

	CCrowdControl *ChooseCC(eSkill skill);
	void SetCCToRandomCharacter(eSkill skill, float fDuration);
	void SetWindDirection(float nDir);
	void DeleteWind();
	void DeleteTornado();
	void DeleteCC();
	int IsGameClear();
	//bool IsGameLose();
	bool ColideCheck(CActor* pActor1 , CActor* pActor2);

	D3DXVECTOR3 GetRandomPartsPosition() override;
	string GetSceneID() override { return m_sStageKey; }
	bool GetStop() override { return m_isTimeStop; }
	float GetTime() override { return m_fGameTime; };
	const vector<CCharacter *> &GetCharacters() override { return m_vecCharacters; }
};
