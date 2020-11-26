#pragma once
#include "CActor.h"

enum class eBluePrintState
{
	Usable,
	Unusable
};

class CBlueprint :
	public CActor
{
private:
	int				n_RotAngleY;
	bool			m_isRightPartsID;
	bool			m_isRightPartsAngle;
	float			m_fProcessivity;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_BlueprintTexture;
public:
	CBlueprint();
	~CBlueprint();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(eEvent eEvent, void* _value) override;
};

