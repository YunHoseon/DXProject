#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"

class IPartGenerator;

enum class ECombinatorType
{
	E_1stAuto,
	E_1stManual,
	E_2stAuto,
	E_2stManual
};

class CPartCombinator :
	public CInteractiveActor ,public IPartGenerator 
{
private:
	ECombinatorType					m_eType;
	vector<ST_PNT_VERTEX>			m_vecVertex;
	LPDIRECT3DTEXTURE9				m_CombinatorTexture;
	std::multimap<string, CParts*>	m_multimapParts;
	std::vector<CParts*>			m_vecDischargeParts;
	ICollisionArea*					m_pPartsInteractCollision;
	D3DXVECTOR3						m_vOnCombinatorPosition;
	CParts*							m_pParts;
	bool							m_isCombine;
	bool							m_isFull;
	
public:
	CPartCombinator(IInteractCenter* pInteractCenter,ECombinatorType eType);
	~CPartCombinator();

public:
	void Update() override;
	void Render() override;
	void Setup(float fAngle, D3DXVECTOR3 vPosition);
	void Interact(CCharacter* pCharacter) override;
	void PartsInteract(CParts* pParts);
	void OnEvent(EEvent eEvent, void* _value) override;
	void CombineParts();
	void AutoCombine();
	void ManualCombine();
	void DischargeParts();
	ICollisionArea* GetInteractCollsion() { return m_pPartsInteractCollision; }
	D3DXVECTOR3 GetPosition() { return m_vPosition; }
	
private:
	CParts* Make() override;

	
};

