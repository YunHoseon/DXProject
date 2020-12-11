#pragma once
#include "CInteractiveActor.h"
class CPharaohCoppin :
	public CInteractiveActor, public IPartGenerator
{
	CStaticMesh*	m_pSMesh;
	bool			m_isInteractCalled;
	float			m_fPassedTime;
public:
	CPharaohCoppin(IInteractCenter* pInteractCenter, D3DXVECTOR3 vPos);
	~CPharaohCoppin();

	void Update() override;
	void Render() override;
	void Interact(CCharacter* pCharacter) override;

	CParts* MakeParts();
	void StopMove();
};

