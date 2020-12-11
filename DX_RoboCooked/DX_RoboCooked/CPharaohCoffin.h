#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"

class CPharaohCoffin :
	public CInteractiveActor, public IPartGenerator
{
	CStaticMesh*	m_pSMesh;
	bool			m_isInteractCalled;
	float			m_fPassedTime;
public:
	CPharaohCoffin(IInteractCenter* pInteractCenter, D3DXVECTOR3 vPos);
	~CPharaohCoffin();

	void Update() override;
	void Render() override;
	void Interact(CCharacter* pCharacter) override;

	CParts* Make();
	void StopMove();
};

