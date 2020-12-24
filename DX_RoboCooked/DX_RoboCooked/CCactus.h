#pragma once
#include "CActor.h"

class CCactus : public CActor
{
	CStaticMesh* m_pSMesh;
public:
	CCactus();
	explicit CCactus(D3DXVECTOR3 vPos);
	virtual ~CCactus();
	void Update() override;
	void Render() override;

	void AddForce(const D3DXVECTOR3& vForce) {}
	void AddAcceleration(const D3DXVECTOR3& vAccel) {}

	void SetScale(float x, float y, float z) override;
	void SetScale(const D3DXVECTOR3& vScale) override;
};
