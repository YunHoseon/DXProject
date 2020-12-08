#pragma once
#include "CActor.h"
class CSandpile :
	public CActor
{
private:
	CStaticMesh*		m_pSMesh;
	ICollisionArea*		m_pCollsionArea;
public:
	CSandpile(IInteractCenter* InteractCenter , D3DXVECTOR3 vPosition);
	~CSandpile();
	void Render() override;
	void Update() override;
};

