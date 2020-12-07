#pragma once
#include "CInteractiveActor.h"
//#include "CPartCombinator.h"

class CPartCombinator;

class CCombinatorButton :
	public CInteractiveActor
{
private:
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_CombinatorBtnTexture;
	CPartCombinator*		m_pPartCombinator;
	CStaticMesh*			m_pSMesh;
public:
	CCombinatorButton(CPartCombinator* pPartCombinator);
	~CCombinatorButton();
public:
	void OnEvent(eEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter) override;
	void Update() override;
	void Render() override;
	void Setup(float fAngle, D3DXVECTOR3 vPosition);

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
};

