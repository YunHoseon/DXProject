#pragma once
#include "ICollisionArea.h"

class CBoxCollision : public ICollisionArea
{
protected:
	
	array<D3DXVECTOR3, 3>			m_arrOriginAxisDir;
	array<D3DXVECTOR3, 3>			m_arrAxisDir;

	array<float, 3>				m_fOriginAxisHalfLen;
	array<float, 3>				m_fAxisHalfLen;

	D3DXVECTOR3	GetCollideNormal(CBoxCollision* pTargetCollider);
public:
	CBoxCollision(D3DXVECTOR3 vOriginPos, D3DXVECTOR3 vSize, D3DXMATRIXA16* pmatWorld = nullptr);
	CBoxCollision(LPD3DXMESH pMesh, D3DXMATRIXA16* pmatWorld = nullptr);
	~CBoxCollision() override;
	void Render() override;
	void Update() override;
	bool CollideToBox(CBoxCollision* pTargetCollider, D3DXVECTOR3* pNormal = nullptr) override;
	bool CollideToSphere(CSphereCollision* pTargetCollider, D3DXVECTOR3* pNormal = nullptr) override;
	void SetScale(float x, float y, float z) override;
	void RotateOriginAxis(float x, float y, float z);
	float GetHeight() override { return m_fAxisHalfLen[1] * 2; }
};
