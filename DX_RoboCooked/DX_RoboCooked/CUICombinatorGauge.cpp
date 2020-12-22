#include "stdafx.h"
#include "CUICombinatorGauge.h"
#include "CUIChargeBoard.h"
#include "CUIChargeFive.h"
#include "CUIChargeFour.h"
#include "CUIChargeThree.h"
#include "CUIChargeTwo.h"
#include "CUIChargeOne.h"
#include "CUIChargeZero.h"


CUICombinatorGauge::CUICombinatorGauge(D3DXVECTOR3 *pPos)
{
	m_isActive = true;
	m_pTargetPosition = pPos;
	Setup();
}


CUICombinatorGauge::~CUICombinatorGauge()
{
}

void CUICombinatorGauge::Setup()
{
	m_vCombinatorUIPosition = D3DXVECTOR3(m_pTargetPosition->x - 1.3f, m_pTargetPosition->y + 3.4f, m_pTargetPosition->z);


	m_pGaugeZero =  new CUIChargeZero(&m_vCombinatorUIPosition);
	m_pGaugeOne =   new CUIChargeOne(&m_vCombinatorUIPosition);
	m_pGaugeTwo =   new CUIChargeTwo(&m_vCombinatorUIPosition);
	m_pGaugeThree = new CUIChargeThree(&m_vCombinatorUIPosition);
	m_pGaugeFour =  new CUIChargeFour(&m_vCombinatorUIPosition);
	m_pGaugeFive =  new CUIChargeFive(&m_vCombinatorUIPosition);

	AddChild(m_pGaugeZero);
	AddChild(m_pGaugeOne);
	AddChild(m_pGaugeTwo);
	AddChild(m_pGaugeThree);
	AddChild(m_pGaugeFour);
	AddChild(m_pGaugeFive);
}

void CUICombinatorGauge::UpdateCombinator(float fElpased, float fMax)
{

	SetChildActive(false);

	float temp = fMax / 5.0f;

	if (temp * 1 > fElpased)
	{
		m_pGaugeZero->SetActive(true);
	}
	else if (temp * 2 > fElpased)
	{
		m_pGaugeOne->SetActive(true);
	}
	else if (temp * 3 > fElpased)
	{
		m_pGaugeTwo->SetActive(true);
	}
	else if (temp * 4 > fElpased)
	{
		m_pGaugeThree->SetActive(true);
	}
	else if (temp * 5 > fElpased)
	{
		m_pGaugeFour->SetActive(true);
	}
	else if (temp * 6 > fElpased)
	{
		m_pGaugeFive->SetActive(true);
	}
}
