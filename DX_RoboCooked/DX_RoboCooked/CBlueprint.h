#pragma once
#include "CInteractiveActor.h"

class CParts;

class CBlueprint :
	public CInteractiveActor
{
private:
	bool				m_isCompleted;			
	string				m_sRightPartsID;		//설계도와 부합하는 파츠 ID
	float				m_fRightPartsAngleY;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	CParts*					m_onBlueprintParts;	//설계도 위의 파츠
	vector<CParts*>*		m_pVecParts;

	ICollisionArea*			m_pInteractCollision;

	LPDIRECT3DTEXTURE9		m_blueprintTexture;
	LPDIRECT3DTEXTURE9		m_completeBlueprintTexture;
	vector<ST_PNT_VERTEX>	m_vecVertex_Multi;
public:
	CBlueprint(string partsID, vector<CParts*>& vecParts, D3DXVECTOR3 position, D3DXVECTOR3 scale, float angle, float partsAngle);
	~CBlueprint();

	void Setup();
	void Update() override;
	void Render() override;
	bool OnEvent(eEvent eEvent, void* _value) override;

	void StoreOnBlueprintParts();
	void CheckBluePrintComplete();

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
	void Interact(CCharacter* pCharacter) override;
	void SetupTexture(string partsID);
	void MultiTexture_Render();

	/*getter setter*/
	bool GetIsCompleted() { return m_isCompleted; }
	void SetPosition(D3DXVECTOR3 vPosition) override;
	void SetPosition(float x, float y, float z) override;
	string GetRightPartsID() { return m_sRightPartsID; }
};

