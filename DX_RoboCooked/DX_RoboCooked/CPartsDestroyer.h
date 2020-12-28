#pragma once
#include "CEventListener.h"
#include "CActor.h"
#include "CUIAcidRain.h"

class CPartsDestroyer : public CEventListener
{
public:
	CPartsDestroyer();
	virtual ~CPartsDestroyer();
private:
	CStaticMesh*	m_pSMesh;
	D3DXMATRIXA16	m_matWorld;
	//LPD3DXMESH		m_pMesh;
	//D3DMATERIAL9	m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTexture;
	float			m_fDuration;
	float			m_fElapseTime;
	bool			m_isRenderable;

	CUIAcidRain		m_cRain;
public:
	bool OnEvent(eEvent eEvent, void* _value) override;
	void Render();
	
	void SetActive(D3DXVECTOR3& vPos, float fDuration);
};
