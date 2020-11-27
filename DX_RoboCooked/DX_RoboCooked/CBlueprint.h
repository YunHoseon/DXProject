#pragma once
#include "CActor.h"

class CParts;
class CBlueprint :
	public CActor
{
private:
	int				m_nRotAngleY;			//설계도의 Y축 회전
	bool			m_isCompleted;			//완성되었는가
	string			m_sRightPartsID;		//설계도와 부합하는 파츠 ID
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_BlueprintTexture;
	CParts*					m_myParts;		//무적 상태를 부여하기 위해
public:
	CBlueprint(string partsID);
	~CBlueprint();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(eEvent eEvent, void* _value) override;
};

