#pragma once
#include "CActor.h"
class CTV;
class IInteractCenter;

class CWall :
	public CActor
{
private:
	int						n_RotAngleX;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_wallTexture;
	//ID3DXMesh*				m_p3DText;
	D3DMATERIAL9			m_stMtlWall;
	CTV*					m_pTV;
public:
	CWall(IInteractCenter* pIntaract);
	~CWall();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(eEvent eEvent, void* _value) override;

	//void Create_Font();
	void ReleaseKey();
};

