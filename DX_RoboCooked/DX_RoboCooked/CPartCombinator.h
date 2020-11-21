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

enum class ECombinatorState
{
	E_LoadPossible,
	E_LoadImpossible
};

class CPartCombinator :
	public CInteractiveActor ,public IPartGenerator 
{
private:
	ECombinatorType					m_eType;
	ECombinatorState				m_eCombinatorState;
	vector<ST_PNT_VERTEX>			m_vecVertex;
	LPDIRECT3DTEXTURE9				m_CombinatorTexture;
	std::multimap<string, CParts*>	m_multimapParts;
	std::vector<CParts*>			m_vecDischargeParts;
	ICollisionArea*					m_pPartsInteractCollision;
	D3DXVECTOR3						m_vOnCombinatorPosition;
	CParts*							m_pParts;
	bool							m_isCombine;
	bool							m_isFull;
	ID3DXMesh*						m_p3DTEXT;
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
	void CombinatorRender();
	ICollisionArea* GetInteractCollsion() { return m_pPartsInteractCollision; }
	D3DXVECTOR3 GetPosition() { return m_vPosition; }
	
private:
	CParts* Make() override;
};

