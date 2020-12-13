#pragma once
#include "CActor.h"
class CTV :
	public CActor
{
private:
	ID3DXMesh*				m_p3DText;
	CStaticMesh*			m_pSMesh;
	string					m_sMin;
	string					m_sSec;
	INT						m_nMin;
	INT						m_nSec;
	FLOAT					m_fTime;
public:
	CTV();
	~CTV();

public:
	void Update() override;
	void Render() override;

	void Create_Font();

	int CalMin(int sec){return sec / 60;}
	int CalSec(int sec){return sec % 60;}
};

