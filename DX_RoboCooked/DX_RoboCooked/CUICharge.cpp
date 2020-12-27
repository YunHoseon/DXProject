#include "stdafx.h"
#include "CUICharge.h"
#include "CUIChargeBoard.h"
#include "CUIChargeFive.h"
#include "CUIChargeFour.h"
#include "CUIChargeThree.h"
#include "CUIChargeTwo.h"
#include "CUIChargeOne.h"
#include "CUIChargeZero.h"

CUICharge::CUICharge(D3DXVECTOR3 *pPos)
	: m_pChargeFive(nullptr), m_pChargeFour(nullptr), m_pChargeThree(nullptr), m_pChargeTwo(nullptr), m_pChargeOne(nullptr), m_pChargeZero(nullptr), m_vChargeUIPosition(0, 0, 0)
{
	m_isActive = true;
	m_pTargetPosition = pPos;
	Setup();
}

CUICharge::~CUICharge()
{
}

void CUICharge::Setup()
{
	m_pChargeZero = new CUIChargeZero(m_pTargetPosition);
	m_pChargeOne = new CUIChargeOne(m_pTargetPosition);
	m_pChargeTwo = new CUIChargeTwo(m_pTargetPosition);
	m_pChargeThree = new CUIChargeThree(m_pTargetPosition);
	m_pChargeFour = new CUIChargeFour(m_pTargetPosition);
	m_pChargeFive = new CUIChargeFive(m_pTargetPosition);

	AddChild(m_pChargeZero);
	AddChild(m_pChargeOne);
	AddChild(m_pChargeTwo);
	AddChild(m_pChargeThree);
	AddChild(m_pChargeFour);
	AddChild(m_pChargeFive);
	SetUIState(eUIState::Target);
}

void CUICharge::UpdateCharging(float fThrowPower, float fMaxThrowPower)
{
	SetChildActive(false);

	float temp = fMaxThrowPower * 0.2f;

	if (fThrowPower < temp * 1)
	{
		m_pChargeZero->SetActive(true);
	}
	else if (fThrowPower < temp * 2)
	{
		m_pChargeOne->SetActive(true);
	}
	else if (fThrowPower < temp * 3)
	{
		m_pChargeTwo->SetActive(true);
	}
	else if (fThrowPower < temp * 4)
	{
		m_pChargeThree->SetActive(true);
	}
	else if (fThrowPower < temp * 5 - EPSILON)
	{
		m_pChargeFour->SetActive(true);
	}
	else
	{
		m_pChargeFive->SetActive(true);
	}
}