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
	D3DXVECTOR3			m_vSize;

public:
	CParts(int nPartsID);
	virtual ~CParts();

	void Setup();
	void Update() override;
	void Render() override;
	
	void OnEvent(EEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter) override;
	
	void DownParts(D3DXVECTOR3 vDir);
	void PartsRotate();
	void MoveParts();
	void SetCombinatorPosition(D3DXVECTOR3 vPosition){ m_vCombinatorPosition = vPosition; }

	/* getter setter */
	
	int GetPartsID() { return m_nPartsID; }
	void SetPartsID(int	ID) { m_nPartsID = ID; }

	float GetWeight() { return m_fWeight; }
	void SetWeight(float weight) { m_fWeight = weight; }

	D3DXVECTOR3 GetSize() { return m_vSize; }
	void SetSize(D3DXVECTOR3 size) { m_vSize = size; }
	
	void SetPosition(D3DXVECTOR3 vPosition) { m_vPosition = vPosition; }
	
	D3DXVECTOR3* GetGrabPosition() { return m_vGrabPosition; }
	void SetGrabPosition(D3DXVECTOR3* vPosition) { m_vGrabPosition = vPosition; }
	
	bool GetMoveParts() { return m_isMoveParts; }
	void SetMoveParts(bool b) { m_isMoveParts = b; }
	D3DXVECTOR3 GetPosition() { return m_vPosition; }

};

