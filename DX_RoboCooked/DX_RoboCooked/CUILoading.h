#pragma once
#include "CUIButton.h"
class CUILoading :
	public CUIButton
{
private:
	bool	m_isLoading;
public:
	CUILoading(D3DXVECTOR2 vPos);
	~CUILoading();

	void Setup() override;
	void Render() override;
};

