#pragma once
#include "CInteractiveActor.h"
class CUITipBoard;

class CTipBoard :
	public CInteractiveActor
{
private:
	CStaticMesh*	m_pSMesh;
	CCharacter*		m_pCharacter;
	CUITipBoard*	m_pTipBoard;
public:
	CTipBoard(D3DXVECTOR3 vPos, string sText);
	~CTipBoard();

	void Update() override;
	void Render() override;
	void Interact(CCharacter* pCharacter) override;

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
	bool OnEvent(eEvent eEvent, void* _value);
	bool ClosePopup(void* _value);
};

