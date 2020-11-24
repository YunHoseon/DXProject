#include "stdafx.h"
#include "CCamera.h"



CCamera::CCamera() :m_vEye(0, 0, -5), m_vLookAt(0, 0, 0), m_vUp(0, 1, 0),
					m_pvTarget(NULL), m_fCameraDistance(11.83f), // 11.0f CameraDistance
					m_isMouseButtonDown(false), m_vCamRotAngle(0.18f, 0, 0) //0.18f
{
}


CCamera::~CCamera()
{
}

void CCamera::Setup(D3DXVECTOR3* pvTarget)
{
	
	m_pvTarget = pvTarget;

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16	matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CCamera::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(0, m_fCameraDistance, -m_fCameraDistance);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);
	if(m_pvTarget)
	{
		m_vLookAt = *m_pvTarget;
		m_vEye += m_vLookAt;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void CCamera::Render()
{
	string sCameraDistance = string("카메라 거리 :") + std::to_string(m_fCameraDistance);
	RECT rc;
	SetRect(&rc, 0, 0, 0, 0);

	// >> :font manager 추가후
	LPD3DXFONT pFont = g_pFontManager->GetFont(CFontManager::eFontType::DEFAULT);
	//<<:

	pFont->DrawTextA(NULL,
		sCameraDistance.c_str(),
		sCameraDistance.length(),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));

	string sAngle = string("카메라 각도 :") + std::to_string(m_vCamRotAngle.x);
	SetRect(&rc, 0, 50, 0, 0);

	pFont = g_pFontManager->GetFont(CFontManager::eFontType::DEFAULT);

	pFont->DrawTextA(NULL,
		sAngle.c_str(),
		sAngle.length(),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));
}

void CCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isMouseButtonDown = true;
		break;
		
	case WM_LBUTTONUP:
		m_isMouseButtonDown = false;
		break;
		
	case WM_MOUSEMOVE:
		if (m_isMouseButtonDown)
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);

			float fDeltaX = (float)ptCurMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)ptCurMouse.y - m_ptPrevMouse.y;
			m_vCamRotAngle.y += (fDeltaX / 100.0f);
			m_vCamRotAngle.x += (fDeltaY / 100.0f);

			if (m_vCamRotAngle.x < -D3DX_PI / 5.0f + 0.0001f)
				m_vCamRotAngle.x = -D3DX_PI / 5.0f + 0.0001f;

			if (m_vCamRotAngle.x > D3DX_PI / 5.0f + 0.0001f)
				m_vCamRotAngle.x = D3DX_PI / 5.0f + 0.0001f;
			
			m_ptPrevMouse = ptCurMouse;
		}
		break;
		
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam)) / 1000.0f;
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
		break;
		
	}
}
