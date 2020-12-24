#pragma once
#include "CActor.h"
class IInteractCenter;
class CTV :
	public CActor
{
private:
	ID3DXMesh*				m_p3DText;
	CStaticMesh*			m_pSMesh;
	std::wstring			m_sTime;
	FLOAT					m_fTime;

	D3DXMATRIXA16*			m_pParentWorld;
	D3DXMATRIXA16			m_matTextLocal;
public:
	CTV(IInteractCenter* pIntaract, D3DXMATRIXA16* pParentWorld = nullptr);
	~CTV();

public:
	void Update() override;
	void Render() override;

	void CreateFont();

	void AddForce(const D3DXVECTOR3& vForce) override {}
	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
};

