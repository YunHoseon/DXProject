#pragma once
#include "CActor.h"

class CWall :
	public CActor
{
private:
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_wallTexture;
public:
	CWall();
	~CWall();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(EEvent eEvent, void* _value) {};

	D3DMATERIAL9					m_stMtlWall;
};

