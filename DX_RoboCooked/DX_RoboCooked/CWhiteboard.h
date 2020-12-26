#pragma once
#include "CInteractiveActor.h"

class CBlueprint;
class CUIWhiteboard;

class CWhiteboard :
	public CInteractiveActor
{
	CStaticMesh*	m_pSMesh;
	CUIWhiteboard*	m_pUIWhiteboard;
	CCharacter*		m_pCharacter;
public:
	CWhiteboard(D3DXVECTOR3 vPos);
	~CWhiteboard();

	void Update() override;
	void Render() override;
	void Interact(CCharacter* pCharacter) override;

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
	bool OnEvent(eEvent eEvent, void* _value);
	bool ClosePopup(void* _value);
	void SetFormula(vector<CBlueprint *>& vBp);

};