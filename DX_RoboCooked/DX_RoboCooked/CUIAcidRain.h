#pragma once
#include "CUIButton.h"

class CUIAcidRain : public CUIButton
{
private:
	void Setup() override;

	float m_fDuration;
	float m_fElapsedTime;
public:
	CUIAcidRain();
	virtual ~CUIAcidRain();
	void Update() override;
	void Render() override;
	bool OnEvent(eEvent eEvent, void* _value) override;
	
};
