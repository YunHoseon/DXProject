#include "stdafx.h"
#include "CUICombinatorGauge.h"
#include "CUIChargeBoard.h"
#include "CUICombinatorGaugeFive.h"
#include "CUICombinatorGaugeFour.h"
#include "CUICombinatorGaugeThree.h"
#include "CUICombinatorGaugeTwo.h"
#include "CUICombinatorGaugeOne.h"


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

	m_pGaugeOne =   new CUICombinatorGaugeOne(&m_vCombinatorUIPosition);
	m_pGaugeTwo =   new CUICombinatorGaugeTwo(&m_vCombinatorUIPosition);
	m_pGaugeThree = new CUICombinatorGaugeThree(&m_vCombinatorUIPosition);
	m_pGaugeFour =  new CUICombinatorGaugeFour(&m_vCombinatorUIPosition);
	m_pGaugeFive =  new CUICombinatorGaugeFive(&m_vCombinatorUIPosition);

	AddChild(m_pGaugeOne);
	AddChild(m_pGaugeTwo);
	AddChild(m_pGaugeThree);
	AddChild(m_pGaugeFour);
	AddChild(m_pGaugeFive);
}

void CUICombinatorGauge::UpdateCombinator(float fElpased, float fMax)
{

	SetChildActive(false);

	float temp = fMax * 0.2f;

	if (temp * 1 > fElpased)
	{
		m_pGaugeOne->SetActive(true);
	}
	else if (temp * 2 > fElpased)
	{
		m_pGaugeTwo->SetActive(true);
	}
	else if (temp * 3 > fElpased)
	{
		m_pGaugeThree->SetActive(true);
	}
	else if (temp * 4 > fElpased)
	{
		m_pGaugeFour->SetActive(true);
	}
	else if (temp * 5 > fElpased)
	{
		m_pGaugeFive->SetActive(true);
	}

}
