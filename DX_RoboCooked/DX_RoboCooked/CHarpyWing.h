#pragma once
#include "CActor.h"

class CHarpyWing : public CStaticMesh
{
public:
	CHarpyWing();
	virtual ~CHarpyWing();

	virtual void SetAnimation() { m_fRotY = 0; m_fElapseTime = 0; }
	virtual void Update(){}
	virtual void Render(LPDIRECT3DTEXTURE9 pBlendTexture = nullptr) override;
protected:
	D3DXMATRIXA16 m_matWorld, m_matLocal;
	float m_fRotY, m_fElapseTime;
	
};

#include "CHarpyWing_L.h"
#include "CHarpyWing_R.h"