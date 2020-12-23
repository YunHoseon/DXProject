#pragma once
#include "CActor.h"

class CWall;

class CBoundaryWall : public CActor
{
private:
	vector<CWall*> m_vecWall;
public:
	CBoundaryWall();
	virtual ~CBoundaryWall();
	void Render() override;
	void Update() override {}
	bool Collide(CActor* target, D3DXVECTOR3* pNormal) override;

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
};
