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
	void PartsInteract(CParts* pParts) override;
	void OnEvent(EEvent eEvent, void* _value) override;
	void CombineParts();

	void ManualCombine();
	void DischargeParts();
	void CombinatorRender();


private:
	CParts* Make() override;
	void Setup(float fAngle, D3DXVECTOR3 vPosition) override;
};

