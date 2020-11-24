#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"
#include "COutlet.h"

enum class ePartVendingState
{
	Usable,
	Unusable
};

class CPartVending :
	public CInteractiveActor, public IPartGenerator
{
private:
	ePartVendingState		m_ePartVendingState;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_PartVendingTexture;
	COutlet*				m_pOutlet;
public:
	CPartVending(COutlet* outlet, IInteractCenter* pInteractCenter, string nPartsID);
	~CPartVending();

	void Setup(float fAngle, D3DXVECTOR3 vPosition);
	void Update() override;
	void Render() override;

	CParts * Make() override;
	void OnEvent(eEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter) override;
};

