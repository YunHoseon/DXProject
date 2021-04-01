#pragma once

class CDashShadow
{
private:
	D3DXMATRIXA16 m_matWorld, m_matView, m_matProj, m_matWorldIT, m_matWVP, m_matViewI, m_matViewIT, m_matWV, m_NebXf;
	float m_fAnimScale, m_fDuration, m_fElapsedTime;
	LPD3DXEFFECT m_pShader;
	LPDIRECT3DTEXTURE9 m_pTexture;

	CStaticMesh* m_pSMesh;
public:
	CDashShadow();
	~CDashShadow();
	void Update();
	void Render();
	void SetAnimation(D3DXMATRIXA16* pmatWorld);
};
