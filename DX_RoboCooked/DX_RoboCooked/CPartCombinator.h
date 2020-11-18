#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"

class IPartGenerator;

enum class ECombinatorType
{
	E_1stAuto,
	E_1stManual,
	E_2stAuto,
	E_2stManual
};

class CPartCombinator :
	public CInteractiveActor ,public IPartGenerator 
{
private:
	ECombinatorType			m_eType;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_CombinatorTexture;
	
public:
	CPartCombinator(IInteractCenter* pInteractCenter,ECombinatorType eType);
	~CPartCombinator();

public:
	void Update() override;
	void Render() override;
	void Setup(float fAngle, D3DXVECTOR3 vecPosition);
	void Interact(CCharacter* pCharacter) override;
	void OnEvent(EEvent eEvent, void* _value);
private:
	CParts* Make() override;

	
};

