#pragma once
#include "CInteractiveActor.h"

class CWhiteboard :
	public CInteractiveActor
{
	CStaticMesh*	m_pSMesh;
public:
	CWhiteboard(D3DXVECTOR3 vPos);
	~CWhiteboard();

	void Update() override;
	void Render() override;
	void Interact(CCharacter* pCharacter) override;
};

