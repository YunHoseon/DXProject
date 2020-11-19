#pragma once
#include "CInteractiveActor.h"

class CPartVending;

enum class EOutletState
{
	E_None,
	E_Loaded
};

class COutlet :
	public CInteractiveActor
{
private:
	EOutletState			m_eOutletState;
	int						m_nPartsID;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_PartVendingTexture;
	
public:
	COutlet(IInteractCenter* pInteractCenter);
	~COutlet();

	void Setup(float fAngle, D3DXVECTOR3 vecPosition, int nPartsID);
	void Update() override;
	void Render() override;
	
	void OnEvent(EEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter);
	//CParts* Make() override;
	D3DXVECTOR3 GetPosition() { return m_vPosition; }
	EOutletState GetState() { return m_eOutletState; }
	void SetState(EOutletState state) { m_eOutletState = state; }
};

