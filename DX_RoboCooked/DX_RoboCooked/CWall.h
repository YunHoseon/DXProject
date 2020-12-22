#pragma once
#include "CActor.h"
class CTV;
class IInteractCenter;

class CWall :
	public CActor
{
private:
	int						m_nRotAngleX;
	LPD3DXMESH				m_pMesh;
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
	bool OnEvent(eEvent eEvent, void* _value) override;

	//void CreateFont();
	void ReleaseKey();

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
};

