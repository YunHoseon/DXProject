#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"

#define PARTS_COUNT 5
class CRandomNumberGenerator;
class CCharacter;

class CPharaohCoffin :
	public CInteractiveActor, public IPartGenerator
{
	CStaticMesh*		m_pSMesh;
	bool				m_isInteractCalled;
	bool				m_isMoveBlocked;
	float				m_fCoolTime;
	float				m_fPassedTime;
	ICollisionArea*		m_pCCCollision;

	string			m_arrPartsID[PARTS_COUNT];	//2´Ü°èÆÄÃ÷ ID
	CRandomNumberGenerator	m_randNumGenerator;
public:
	CPharaohCoffin(IInteractCenter* pInteractCenter, D3DXVECTOR3 vPos);
	~CPharaohCoffin();

	void Update() override;
	void Render() override;
	void Interact(CCharacter* pCharacter) override;

	CParts* Make();

	void AddAcceleration(const D3DXVECTOR3& vAccel) {}
	void AddForce(const D3DXVECTOR3& vForce) {}
};

