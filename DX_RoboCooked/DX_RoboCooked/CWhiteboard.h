#pragma once
#include "CInteractiveActor.h"

class CUIWhiteboard;

class CWhiteboard :
	public CInteractiveActor
{
	CStaticMesh*	m_pSMesh;
	CUIWhiteboard*	m_pUIWhiteboard;
public:
	CWhiteboard(D3DXVECTOR3 vPos);
	~CWhiteboard();

	void Update() override;
	void Render() override;
	void Interact(CCharacter* pCharacter) override;
};

