#pragma once
#include "CInteractiveActor.h"
#include "CPartCombinator.h"
#include "CStaticMesh.h"
class CCharacter;
class CParts :
	public CInteractiveActor
{
private:
	D3DXVECTOR3						m_vCombinatorPosition;
	D3DXVECTOR3*					m_vGrabPosition;

	//ST_SPHERE						m_sphere;
	//LPD3DXMESH						m_pMeshSphere;
	//D3DMATERIAL9					m_stMtlParts;

	CStaticMesh						m_cMesh;

	bool							m_isMoveParts;
	string							m_sPartsID;
	//int								m_nRotAngleY;
	eCombinatorPartsLevel			m_eLevel;
	string							m_sFormula;
	CPartCombinator*				m_pPartsCombinator;


public:
	CParts(string sPartsID, string sFormula, float fMass);
	CParts(CParts* pParts);
	virtual ~CParts();

	void Setup(D3DXVECTOR3& vScale);
	void Update() override;
	void Render() override;
	CParts* Clone();
	
	void OnEvent(eEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter) override;
	
	void ThrowParts(D3DXVECTOR3 vForce);
	void PartsRotate();
	void MoveParts();
	void SetCombinatorPosition(D3DXVECTOR3 vPosition){ m_vCombinatorPosition = vPosition; }

	CStaticMesh* GetStaticMesh() { return &m_cMesh; }

	/* getter setter */
	
	string GetPartsID() { return m_sPartsID; }
	void SetPartsID(string	ID) { m_sPartsID = ID; }

	//int GetPartsAngle() { return m_nRotAngleY; }
	
	string GetFormula() { return m_sFormula; }
	void SetFormula(string sFormula) { m_sFormula = sFormula; }
	
	D3DXVECTOR3* GetGrabPosition() { return m_vGrabPosition; }
	void SetGrabPosition(D3DXVECTOR3* vPosition);

	bool GetMoveParts() { return m_isMoveParts; }
	void SetMoveParts(bool b) { m_isMoveParts = b; }

	eCombinatorPartsLevel GetCombinePartsLevel() const { return m_eLevel; }

	void SetCPartCombinator(CPartCombinator* p) { m_pPartsCombinator = p; }

	void AddForce(const D3DXVECTOR3& vForce) override;
	void AddAcceleration(const D3DXVECTOR3& vAccel) override;
};

