#pragma once
#include "CActor.h"
class CSandpile :
	public CActor
{
private:
	CStaticMesh*		m_pSMesh;
	ICollisionArea*		m_pCollisionArea;
public:
	CSandpile(IInteractCenter* InteractCenter , D3DXVECTOR3 vPosition);
	~CSandpile();
	void Render() override;
	void Update() override;

	void AddForce(const D3DXVECTOR3& vForce) override {}
	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
};

