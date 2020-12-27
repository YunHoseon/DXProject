#pragma once
#include "CUIButton.h"


class CUIChargeBoard;


class CUICombinatorGauge :
	public CUIButton
{
private:
	CUIChargeBoard*		m_pGaugeFive;
	CUIChargeBoard*		m_pGaugeFour;
	CUIChargeBoard*		m_pGaugeThree;
	CUIChargeBoard*		m_pGaugeTwo;
	CUIChargeBoard*		m_pGaugeOne;

	D3DXVECTOR3			m_vCombinatorUIPosition;

public:
	CUICombinatorGauge(D3DXVECTOR3 *pPos);
	~CUICombinatorGauge();


public:
	void Setup() override;
	void UpdateCombinator(float fElpased, float fMax);

	


};

