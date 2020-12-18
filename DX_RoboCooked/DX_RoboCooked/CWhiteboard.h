#pragma once
#include "CInteractiveActor.h"

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

	bool OnEvent(eEvent eEvent, void* _value);
	bool ClosePopup(void* _value);
};

