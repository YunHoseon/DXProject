#pragma once
#include "ICollisionArea.h"

class CBoxCollision;

class CSphereCollision : public ICollisionArea
{
protected:
	float			m_fOriginRadius;
	float			m_fRadius;
	LPD3DXMESH		m_pMesh;
public:
	explicit CSphereCollision(D3DXVECTOR3 vOriginPos, float fRadius = 1.0f, D3DXMATRIXA16* pmatWorld = nullptr);
	explicit CSphereCollision(LPD3DXMESH pMesh, D3DXMATRIXA16* pmatWorld = nullptr);
	~CSphereCollision() override;
	void Render() override;
	void Update() override;
	float GetRadius() { return m_fRadius; }
	bool CollideToBox(CBoxCollision* pTargetCollider, D3DXVECTOR3* pNormal) override;
	bool CollideToSphere(CSphereCollision* pTargetCollider, D3DXVECTOR3* pNormal) override;
	void SetScale(float x, float y, float z) override;
};
