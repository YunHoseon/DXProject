#pragma once
#include "CPartCombinator.h"
class CPartManualCombinator :
	public CPartCombinator
{
private:
	bool							m_isTimeCheck;

public:
	CPartManualCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition);
	~CPartManualCombinator();

	void Update() override;
	void Render() override;

	void Interact(CCharacter* pCharacter) override;
	void PartsInteract(CParts* pParts) override;
	void OnEvent(EEvent eEvent, void* _value) override;
	void CombineParts();
	void PartsMakeTime() override;

	void ManualCombine();
	void DischargeParts() override;
	void CombinatorRender() override;


private:
	CParts* Make() override;
	void Setup(float fAngle, D3DXVECTOR3 vPosition) override;
};

