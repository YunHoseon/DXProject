#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"
class CPartStorage :
	public CInteractiveActor ,IPartGenerator 
{
private:
	vector<ST_PNT_VERTEX>	m_vecVertex; 
	LPDIRECT3DTEXTURE9		m_storageTexture;
public:
	CPartStorage();
	~CPartStorage();


public:
	void Update() override;
	void Render() override;
	void Setup(float fAngle ,D3DXVECTOR3 vecPosition);
	void OnEvent(EEvent eEvent, void* _value);
	void Interact() override;

private:
	void Make() override;
	
};

