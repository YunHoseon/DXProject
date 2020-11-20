#pragma once
#include "ICollisionArea.h"

class CBoxCollision : public ICollisionArea
{
protected:
	
	D3DXVECTOR3			m_vOriginAxisDir[3];
	D3DXVECTOR3			m_vAxisDir[3];

	float				m_fAxisHalfLen[3];

public:
	CBoxCollision(D3DXVECTOR3 vOriginPos, D3DXVECTOR3 vSize, D3DXMATRIXA16* pmatWorld = nullptr);
	~CBoxCollision() override;
	void Render() override;
	void Update() override;
	bool CollideToBox(CBoxCollision* pTargetCollider, D3DXVECTOR3* pNormal = nullptr) override;
	bool CollideToSphere(CSphereCollision* pTargetCollider, D3DXVECTOR3* pNormal = nullptr) override;
};
