#pragma once

class CSphereCollision;
class CBoxCollision;

class ICollisionArea
{
public:
	enum class eColideType { Box, Sphere };
protected:
	eColideType			m_eType;
	bool				m_isCollide; // render할 때 색 변환을 위한 변수
	bool				m_isActive;
	D3DCOLOR			m_stColor[2];

	D3DXVECTOR3			m_vOriginCenterPos;
	D3DXVECTOR3			m_vCenterPos;

	D3DXMATRIXA16*		m_pmatWorldTM;
		
public:
	ICollisionArea();
	virtual ~ICollisionArea() {}
	const D3DXVECTOR3& GetCenter() { return m_vCenterPos; }

	bool Collide(ICollisionArea* pTargetCollider, D3DXVECTOR3* pNormal = nullptr);
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual bool CollideToBox(CBoxCollision* pTargetCollider, D3DXVECTOR3* pNormal) = 0;
	virtual bool CollideToSphere(CSphereCollision* pTargetCollider, D3DXVECTOR3* pNormal) = 0;
	void SetIsCollide(bool b) { m_isCollide = b; }
	bool GetActive() { return m_isActive; }
	void SetActive(bool b) { m_isActive = b; }
};
