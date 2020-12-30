#pragma once
#include "CSingleton.h"

#define g_pRenderShadowManager CRenderShadowManager::GetInstance()

class CRenderShadowManager : public CSingleton<CRenderShadowManager>
{
	//D3DXVECTOR4			m_vWorldLightPosition;
	//LPD3DXEFFECT		m_pCreateShadowShader;
	//LPDIRECT3DTEXTURE9	m_pShadowRenderTarget;
	//LPDIRECT3DSURFACE9	m_pShadowDepthStencil;
	D3DXMATRIXA16 m_matLightView;
	D3DXMATRIXA16 m_matLightProjection;

public:
	CRenderShadowManager();
	~CRenderShadowManager();
	
	Synthesize_Pass_by_Ref(D3DXVECTOR4, m_vWorldLightPosition, WorldLightPosition);
	Synthesize(LPD3DXEFFECT, m_pCreateShadowShader, CreateShadowShader);
	Synthesize(LPD3DXEFFECT, m_pApplyShadowShader, ApplyShadowShader);
	Synthesize(LPDIRECT3DTEXTURE9, m_pShadowRenderTarget, ShadowRenderTarget);
	Synthesize(LPDIRECT3DSURFACE9, m_pShadowDepthStencil, ShadowDepthStencil);

	//LPDIRECT3DTEXTURE9 GetShadowRenderTarget();

	D3DXMATRIXA16& CalAndSetLightView();
	D3DXMATRIXA16& CalAndSetLightProjection();
};

