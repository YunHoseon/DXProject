#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"

class IPartGenerator;


enum class eCombinatorPartsLevel
{
	ONE,
	TWO,
	THREE,
	FOUR
};

enum class eCombinatorLoadState
{
	LoadPossible,
	LoadImpossible
};

enum class eCombinatorActionState
{
	Usable,
	Unusable
};


class CPartCombinator :
	public CInteractiveActor ,public IPartGenerator 
{
protected:
	eCombinatorPartsLevel			m_eLevel;
	eCombinatorLoadState			m_eCombinatorLoadState;
	eCombinatorActionState			m_eCombinatorActionState;
	vector<ST_PNT_VERTEX>			m_vecVertex;
	LPDIRECT3DTEXTURE9				m_CombinatorTexture;
	std::multimap<string, CParts*>	m_multimapParts;
	std::vector<CParts*>			m_vecDischargeParts;
	ICollisionArea*					m_pPartsInteractCollision;
	//D3DXVECTOR3						m_vOnCombinatorPosition;
	vector<D3DXVECTOR3>				m_vecOnCombinatorPosition;
	CParts*							m_pParts;
	bool							m_isCombine;
	float							m_fElapsedTime;
	float							m_fCombineTime;
	INT								m_nPartsCount;
	INT								m_nMaxPartsCount;
	CStaticMesh*					m_pSMesh;


public:
	CPartCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition) ;
	virtual ~CPartCombinator();

public:
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	
	virtual void Interact(CCharacter* pCharacter) override = 0;
	virtual void PartsInteract(CParts* pParts) = 0 ;
	virtual void CombineParts() = 0;
	virtual void DischargeParts() = 0;
	virtual void InsertParts(CParts* p) = 0 ;
	virtual void ReadytoCarryParts() = 0;
	
	ICollisionArea* GetInteractCollsion() const { return m_pPartsInteractCollision; };
	D3DXVECTOR3 GetPosition() const { return m_vPosition; };
	eCombinatorPartsLevel GetCombinPartsLevel() const { return m_eLevel; }
	eCombinatorLoadState GetCombinatorLoadState() { return m_eCombinatorLoadState; }
	void SetCombinatorLoadState(eCombinatorLoadState st) { m_eCombinatorLoadState = st; }
	INT GetCombinatorPartsCount() { return m_nPartsCount; }


	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
private:
	CParts* Make() override = 0;
	virtual void Setup(float fAngle, D3DXVECTOR3 vPosition){};
};