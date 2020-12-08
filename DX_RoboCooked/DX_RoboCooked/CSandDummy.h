#pragma once
#include "CActor.h"
class CSandDummy :
	public CActor
{
private:
	CStaticMesh*		m_pSMesh;
	ICollisionArea*		m_pCollsionArea;
public:
	CSandDummy(IInteractCenter* InteractCenter , D3DXVECTOR3 vPosition);
	~CSandDummy();
	void Render() override;
	void Update() override;
};

