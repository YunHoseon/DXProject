#pragma once
#include "CPartCombinator.h"
class CPartManualCombinator :
	public CPartCombinator
{
public:
	CPartManualCombinator(IInteractCenter* pInteractCenter, eCombinatorLevel eType, float fAngle, D3DXVECTOR3 vPosition);
	~CPartManualCombinator();

	void Update() override;
	void Render() override;

	void Interact(CCharacter* pCharacter) override;
	void PartsInteract(CParts* pParts);
	void OnEvent(EEvent eEvent, void* _value) override;
	void CombineParts();
	void CombineManualParts();
	void CombineAutoParts();
	void ManualCombine();
	void DischargeParts();
	void CombinatorRender();
	ICollisionArea* GetInteractCollsion() const { return m_pPartsInteractCollision; }
	D3DXVECTOR3 GetPosition() const { return m_vPosition; }

private:
	CParts* Make() override;
	void Setup(float fAngle, D3DXVECTOR3 vPosition) override;
};

