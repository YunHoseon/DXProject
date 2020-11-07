#pragma once
class CPyramid;


class CGrid
{
public:
	CGrid();
	~CGrid();

private:
	vector<ST_PC_VERTEX>			m_vecVertex;


	vector<CPyramid*>				m_vecPyramid;
	D3DMATERIAL9					m_stMt1;
	D3DMATERIAL9					m_stMt2;

	LPDIRECT3DTEXTURE9				m_PlaneTexture;
	LPDIRECT3DTEXTURE9				m_PlaneTexture2;


public:
	void Setup(int nNumHalfTile = 15, float fInterval = 1.0f);
	void Render();
};

