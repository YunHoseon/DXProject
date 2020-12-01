#pragma once
#include "CActor.h"

class CInteractiveActor;
class CParts;
class CBoxCollision;

class CBlueprint :
	public CActor
{
private:
	int				m_nRotAngleY;
	bool			m_isCompleted;			//완성되었는가
	string			m_sRightPartsID;		//설계도와 부합하는 파츠 ID
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_blueprintTexture;
	CParts*					m_onBlueprintParts;	//설계도 위의 파츠
	vector<CInteractiveActor*>*		m_pVecParts;
	CBoxCollision*		m_pInteractCollision;			//파츠가 플레이어에게 밀리지 않고 상호작용할 수 있게
public:
	CBlueprint(string partsID, vector<CInteractiveActor*>& vecParts);
	~CBlueprint();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(eEvent eEvent, void* _value) override;

	void CheckOnBlueprintParts();
};

