#pragma once
#include "CActor.h"
class IInteractCenter;
class CTV :
	public CActor
{
private:
	ID3DXMesh*				m_p3DText;
	CStaticMesh*			m_pSMesh;
	std::wstring			m_sTime;
	FLOAT					m_fTime;
public:
	CTV(IInteractCenter* pIntaract);
	~CTV();

public:
	void Update() override;
	void Render() override;

	void Create_Font();

	string CalMin(int sec);
	string CalSec(int sec);
};

