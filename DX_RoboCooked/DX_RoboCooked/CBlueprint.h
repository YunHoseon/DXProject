#pragma once
#include "CInteractiveActor.h"

//class CInteractiveActor;
class CParts;
class CBlueprint :
	public CInteractiveActor
{
private:
	int				m_nRotAngleY;			//설계도의 Y축 회전
	bool			m_isCompleted;			//완성되었는가
	string			m_sRightPartsID;		//설계도와 부합하는 파츠 ID
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_blueprintTexture;
	CParts*					m_onBlueprintParts;	//설계도 위의 파츠
	vector<CInteractiveActor*>*		m_pVecParts;
	ICollisionArea*		m_pInteractCollision;
public:
	CBlueprint(string partsID, vector<CInteractiveActor*>& vecParts);
	~CBlueprint();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(eEvent eEvent, void* _value) override;

	void CheckOnBlueprintParts();

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
	void Interact(CCharacter* pCharacter) override;
};

