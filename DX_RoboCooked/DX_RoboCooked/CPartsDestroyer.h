#pragma once
#include "CEventListener.h"

class CPartsDestroyer : public CEventListener
{
public:
	CPartsDestroyer();
	virtual ~CPartsDestroyer();
private:
	LPD3DXMESH		m_pMesh;
	D3DMATERIAL9	m_stMtl;
	float			m_fDuration;
	float			m_fElapseTime;
	bool			m_isRenderable;
	D3DXMATRIXA16	m_matWorld;
public:
	bool OnEvent(eEvent eEvent, void* _value) override;
	
	void Render();
	
	void SetActive(D3DXVECTOR3& vPos, float fDuration, float fRadius);
};
