#pragma once
#include "CUITexture.h"

class CUIHeart : public CUITexture
{
private:
	D3DXMATRIXA16 m_matRotate, m_matWorld, m_matLocal;
	float m_fRot, m_fElapsedTime, m_fDuration;
public:
	CUIHeart();
	virtual ~CUIHeart();


	void Update() override;
	void Render() override;
};
