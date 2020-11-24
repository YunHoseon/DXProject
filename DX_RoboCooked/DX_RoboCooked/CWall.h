#pragma once
#include "CActor.h"

class CWall :
	public CActor
{
private:
	int						n_RotAngleX;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_wallTexture;
	ID3DXMesh*				m_p3DText;

public:
	CWall();
	~CWall();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(EEvent eEvent, void* _value) {};

	void Create_Font();
	D3DMATERIAL9					m_stMtlWall;
};

