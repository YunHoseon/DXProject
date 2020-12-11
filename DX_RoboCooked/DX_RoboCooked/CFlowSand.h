#pragma once
#include "CTile.h"
class CFlowSand :
	public CTile
{
protected:
	CStaticMesh* m_pUpperMesh;
	D3DXMATRIXA16 m_matWorld_Upper;
public:
	CFlowSand(D3DXVECTOR3 vPosition);
	~CFlowSand();

	void Render() override;
	void SetPosition(D3DXVECTOR3 vPosition) override;
	void SetPosition(float x, float y, float z) override;
};

