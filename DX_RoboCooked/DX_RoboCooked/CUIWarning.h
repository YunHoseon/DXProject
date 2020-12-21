#pragma once
#include "CUIButton.h"
class CUIWarning :
	public CUIButton
{
private:
	float	m_fElapsedTime;
	int		m_nRepeatCount;
	int		m_nBlinkCount;
	bool	m_isBlink;
public:
	CUIWarning();
	~CUIWarning();

public:
	void Setup()override;
	bool OnEvent(eEvent eEvent, void* _value);
	bool TickUpdate(void* _value);

};

