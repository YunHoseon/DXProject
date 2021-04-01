#pragma once
#include "CParts.h"


class CDashShadow;
class ICollisionArea;
class CGameScene;
class CCrowdControl;
class CSkinnedMesh;
class CUICharge;

enum class ePlayerState
{
	None, 
	Grab 
};

enum eAnimState
{
	Idle,
	Run,
	Spin,
	Stun
};

class CCharacter :public CActor
{
protected:
	CSkinnedMesh*		m_pSkinnedMesh;
	ePlayerState		m_ePlayerState;
	ICollisionArea*		m_pInteractCollision;

	D3DXVECTOR3			m_vGrabPartsPosition;
	CParts*				m_pParts;

	D3DXVECTOR3			m_vDefaultPosition;
	
	
	array<float, 3>		m_arrElapsedTime;
	array<float, 3>		m_arrCoolDown;
	array<bool, 3>		m_arrKeyDown;
	bool				m_isMoveKeyDown;
	bool				m_isDash;
	// ������
	const ST_PLAYER_INPUTKEY* m_pInputKey;
	//LPD3DXMESH			m_pMesh;
	//D3DMATERIAL9		m_stMtl;
	float				m_fMinThrowPower;
	float				m_fMaxThrowPower;
	float				m_fThrowPower;
	float				m_fThrowPowerUpSpeed;
	float				m_fMaxSpeed;
	
	ICollisionArea*		m_pOverlappedSandpile;

	CCrowdControl*		m_pCC;
	CUICharge*			m_pCharge;

	CDashShadow*		m_pDashShadow;
public:
	CCharacter(int nPlayerNum);
	virtual ~CCharacter();
	virtual void Render();
	virtual void Update();
	virtual bool OnEvent(eEvent eEvent, void* _value) override;
	virtual void PressKey(void* _value);
	virtual void ReleaseKey(void* _value);
	virtual void SetKeyChange(void* _value);
	virtual void Move();
	virtual void Rotate(float fTargetRot);
	virtual void AddForce(const D3DXVECTOR3& vForce) override;
	virtual void SetForce(const D3DXVECTOR3& vForce = g_vZero) override;
	virtual float GetMass() override;
	virtual void Reset();
	
	void DeleteCC();
	void SetAnimState();
	
	/*getter setter*/
	ST_PLAYER_INPUTKEY GetInputKey() { return *m_pInputKey; }
	D3DXVECTOR3& GetGrabPartsPosition() { return m_vGrabPartsPosition; }
	ICollisionArea* GetInteractCollsion() { return m_pInteractCollision; }
	
	ePlayerState GetPlayerState() { return m_ePlayerState; }
	void SetPlayerState(ePlayerState state) { m_ePlayerState = state; }
	
	CParts* GetParts() { return m_pParts; }
	void SetParts(CParts* pParts) { m_pParts = pParts; }

	ICollisionArea* GetOverlappedSandpile() { return m_pOverlappedSandpile; }
	void SetOverlappedSandpile(ICollisionArea* p) { m_pOverlappedSandpile = p; }

	CCrowdControl* GetCC() { return m_pCC; }
	void SetCC(CCrowdControl* cc);

	virtual void SetDefaultPosition(D3DXVECTOR3 vPos) { m_vDefaultPosition = vPos; }

	virtual void CreateShadowMap() override;
};

