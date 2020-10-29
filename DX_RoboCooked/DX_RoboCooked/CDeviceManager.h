#pragma once

#include "CSingleton.h"

#define g_pDeviceManager CDeviceManager::GetInstance()
#define g_pD3DDevice CDeviceManager::GetInstance()->GetDevice()

class CDeviceManager : public CSingleton<CDeviceManager>
{
	//Singletone(CDeviceManager);

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
public:
	CDeviceManager();
	~CDeviceManager();
	LPDIRECT3DDEVICE9	GetDevice();
	void Destroy();
	
};
