#pragma once
#include "CInteractiveActor.h"

class CCharacter;
class CParts :
	public CInteractiveActor
{
private:
	D3DXVECTOR3			m_vCombinatorPosition;
	D3DXVECTOR3*		m_vGrabPosition;

	ST_SPHERE			m_sphere;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlParts;
	bool				m_isMoveParts;
	int					m_nPartsID;
	float				m_fRotAngle;
	float				m_fWeight;

public:
	CParts(int nPartsID);
	virtual ~CParts();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(EEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter) override;
	void SetGrabPosition(D3DXVECTOR3* vPosition) { m_vGrabPosition = vPosition; }
	D3DXVECTOR3* GetGrabPosition() { return m_vGrabPosition; }
	void DownParts(D3DXVECTOR3 vDir);
	void PartsRotate();
	int GetPartsID() { return m_nPartsID; }
	void MoveParts();
	void SetCombinatorPosition(D3DXVECTOR3 vPosition){ m_vCombinatorPosition = vPosition; }
	bool GetMoveParts() { return m_isMoveParts; }
	void SetMoveParts(bool b) { m_isMoveParts = b; }

};

