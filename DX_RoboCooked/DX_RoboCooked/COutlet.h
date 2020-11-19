#pragma once
#include "CActor.h"
#include "IPartGenerator.h"

class CPartVending;
class COutlet :
	public CActor, IPartGenerator
{
private:
	int					m_nPartsID;
	CPartVending*		m_pGeneratorSwitch;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;

	LPD3DXMESH			m_pMeshCube;
	D3DMATERIAL9		m_stMtlCube;
public:
	COutlet(IInteractCenter* pInteractCenter);
	~COutlet();

	void Setup(float fAngle, D3DXVECTOR3 vecPosition, int nPartsID);
	void Update() override;
	void Render() override;
	
	void OnEvent(EEvent eEvent, void* _value);
	CParts* Make() override;
};

