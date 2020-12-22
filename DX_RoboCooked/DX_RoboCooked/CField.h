#pragma once
#include "CActor.h"
#include "CTile.h"

class CField :
	public CActor
{
public:
	CField(eTileType type);
	virtual ~CField();

public:
	void Render() override;
	void Update() override {}
	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
	bool Collide(CActor* target, D3DXVECTOR3* pNormal) override;
	//bool Collide(CActor* target, D3DXVECTOR3* pNormal) override;
private:
	vector<CTile*>					m_vecTile;
	D3DMATERIAL9					m_stMtlTile;
	eTileType m_eTileType;

	void Setup(int iWidth = 30,int iHeight = 14);
	float m_fMinX, m_fMaxX, m_fMinZ, m_fMaxZ;
	const float m_fVoidMaxX, m_fVoidMaxZ, m_fVoidMinX, m_fVoidMinZ;
};

