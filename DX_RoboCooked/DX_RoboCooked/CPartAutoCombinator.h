#pragma once
#include "CPartCombinator.h"
class CPartAutoCombinator :
	public CPartCombinator
{
public:
	CPartAutoCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition);
	~CPartAutoCombinator();

	void Update() override;
	void Render() override;
	void Interact(CCharacter* pCharacter) override;
	void PartsInteract(CParts* pParts) override;
	void OnEvent(eEvent eEvent, void* _value) override;
	void CombineParts() override;


	void DischargeParts() override;
	void InsertParts(CParts* p) override;
	void ReadytoCarryParts() override;


private:
	CParts* Make() override;
	void Setup(float fAngle, D3DXVECTOR3 vPosition) override;
};

