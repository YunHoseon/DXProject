#pragma once
#include "CUIButton.h"

class CUIWind : public CUIButton
{
protected:
	float m_fDirect;
	float m_fSpeed;
	const float m_fMargin;
public:
	CUIWind();
	virtual ~CUIWind();

	void ResetPosition();
	void SetAnimation(float fDirect);
	void Update() override;
	void Render() override;
	void Setup() override {}
};
