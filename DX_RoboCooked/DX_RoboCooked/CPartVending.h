#pragma once
#include "CInteractiveActor.h"
#include "COutlet.h"

class CPartVending : public CInteractiveActor
{
private:
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_PartVendingTexture;
	COutlet*				m_pOutlet;
public:
	CPartVending(COutlet* outlet);
	~CPartVending();

	void Setup(float fAngle, D3DXVECTOR3 vPosition);
	void Update() override;
	void Render() override;

	void OnEvent(EEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter) override;
};

