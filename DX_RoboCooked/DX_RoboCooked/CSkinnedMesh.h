﻿#pragma once

struct ST_BONE;

class CSkinnedMesh
{
public:
	CSkinnedMesh();
	~CSkinnedMesh();
protected:
	LPD3DXFRAME		m_pRoot;
	LPD3DXANIMATIONCONTROLLER		m_pAnimController;

	float			m_fBlendTime;
	float			m_fPassedBlendTime;
	bool			m_isAnimBlend;
	double			m_dAnimPeriod;
	float			m_fAnimTime;
	bool			m_isInputOn;

	//enum AnimSet { ATK01, ATK02, ATK03, RUN, IDLE };
	int				m_nCurrentAnimIndex;
	D3DXMATRIXA16 * m_pmatWorldTM;
public:
	void Setup(char* szFolder, char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void RenderWithShadow(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);

	int GetCurrentAnimIndex() const { return m_nCurrentAnimIndex; }
private:
	Synthesize(D3DXVECTOR3, m_vMin, Min);
	Synthesize(D3DXVECTOR3, m_vMax, Max);

public:
	CSkinnedMesh(char * szFolder, char* szFileName);
	void Load(char* szFolder, char* szFileName);
	void Destroy();
	void UpdateAndRender();
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void SetRandomTrackPosition();

	void SetTransform(D3DXMATRIXA16 * pmat);
	D3DXMATRIXA16* GetTransform() { return m_pmatWorldTM; }
	void DeleteTransform() { SafeDelete(m_pmatWorldTM); }
	double GetCurrentAnimPeriod();
	LPD3DXANIMATIONCONTROLLER GetAnimController() { return m_pAnimController; }
	
};
