#pragma once
#include "CInteractiveActor.h"

class CPartVending;
class CParts;
enum class eOutletState
{
	None,
	Loaded
};

class COutlet :
	public CInteractiveActor
{
private:
	eOutletState			m_eOutletState;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_PartVendingTexture;
	CParts*					m_pMyParts;
	
public:
	COutlet(IInteractCenter* pInteractCenter);
	~COutlet();

	void Setup(float fAngle, D3DXVECTOR3 vecPosition);
	void Update() override;
	void Render() override;
	
	void OnEvent(eEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter);
	void AcceptPartsFromVending(CParts* parts);

	const D3DXVECTOR3& GetPosition() { return m_vPosition; }
	eOutletState GetState() { return m_eOutletState; }
	void SetState(eOutletState state) { m_eOutletState = state; }

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
};

