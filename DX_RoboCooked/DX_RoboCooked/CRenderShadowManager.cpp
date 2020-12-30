#include "stdafx.h"
#include "CRenderShadowManager.h"


CRenderShadowManager::CRenderShadowManager() :
	m_vWorldLightPosition(D3DXVECTOR4(16.0f, 32.0f, 16.0f, 1.0f))
	, m_pCreateShadowShader(nullptr)
	, m_pShadowRenderTarget(nullptr)
	, m_pShadowDepthStencil(nullptr)
{
	m_pCreateShadowShader = g_pShaderManager->GetShader("data/Shader/CreateShadow.fx");

	m_pApplyShadowShader = g_pShaderManager->GetShader("data/Shader/TexLightApplyShadow.fx");

	const int shadowMapSize = 2048;

	g_pD3DDevice->CreateTexture(shadowMapSize, shadowMapSize, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pShadowRenderTarget, NULL);

	g_pD3DDevice->CreateDepthStencilSurface(shadowMapSize, shadowMapSize, D3DFMT_D24X8,
		D3DMULTISAMPLE_NONE, 0, TRUE, &m_pShadowDepthStencil, NULL);
}


CRenderShadowManager::~CRenderShadowManager()
{
	SafeRelease(m_pCreateShadowShader);
	SafeRelease(m_pApplyShadowShader);
	SafeRelease(m_pShadowRenderTarget);
	SafeRelease(m_pShadowDepthStencil);
}

//LPDIRECT3DTEXTURE9 CRenderShadowManager::GetShadowRenderTarget()
//{
//	return m_pShadowRenderTarget;
//}

D3DXMATRIXA16& CRenderShadowManager::CalAndSetLightView()
{
	D3DXVECTOR3 vEyePt(m_vWorldLightPosition.x, m_vWorldLightPosition.y, m_vWorldLightPosition.z);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_matLightView, &vEyePt, &vLookatPt, &vUpVec);
	m_pCreateShadowShader->SetMatrix("gLightViewMatrix", &m_matLightView);
	m_pApplyShadowShader->SetMatrix("gLightViewMatrix", &m_matLightView);
	return m_matLightView;
}

D3DXMATRIXA16& CRenderShadowManager::CalAndSetLightProjection()
{
	D3DXMatrixPerspectiveFovLH(&m_matLightProjection, D3DX_PI / 4.0f, 1, 1.0f, 1000.0f);
	m_pCreateShadowShader->SetMatrix("gLightProjectionMatrix", &m_matLightProjection);
	m_pApplyShadowShader->SetMatrix("gLightProjectionMatrix", &m_matLightProjection);
	return m_matLightProjection;
}
