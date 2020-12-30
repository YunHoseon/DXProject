#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"

class CSkinnedMesh;

class CPartStorage :
	public CInteractiveActor ,public IPartGenerator 
{
private:
	CSkinnedMesh*			m_pSkinnedMesh;
	bool					m_isInteractCalled;
	float					m_fPassedTime;
public:
	CPartStorage(IInteractCenter* pInteractCenter);
	~CPartStorage();

public:
	void Update() override;
	void Render() override;
	void Setup(float fAngle ,D3DXVECTOR3 vPosition,string sPartsID);
	void Interact(CCharacter* pCharacter) override;
	
	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}

	void CreateShadowMap() override;
private:
	CParts* Make() override;
};

