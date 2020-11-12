#pragma once
#include "CActor.h"
#include "CTile.h"


class CField :
	public CActor
{
public:
	CField();
	virtual ~CField();

public:
	void Setup(int iWidth = 16,int iHeight = 12);
	void Render() override;
	void Update() override;
private:
	vector<CTile*>					m_vecTile;
	D3DMATERIAL9					m_stMtlTile;
	LPD3DXMESH						m_pCubeTile;
	
};

