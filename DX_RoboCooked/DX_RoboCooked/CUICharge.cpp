#include "stdafx.h"
#include "CUICharge.h"
#include "CUIChargeBoard.h"
#include "CUIChargeFive.h"
#include "CUIChargeFour.h"
#include "CUIChargeThree.h"
#include "CUIChargeTwo.h"
#include "CUIChargeOne.h"
#include "CUIChargeZero.h"




CUICharge::CUICharge(D3DXVECTOR3* pPos, float* pfThrowPower, float fMaxThrowPower)
	: m_pfThrowPower(pfThrowPower)
	, m_fMaxThrowPower(fMaxThrowPower)
	, m_pChargingBoard(nullptr)
	, m_pChargeFive(nullptr)
	, m_pChargeFour(nullptr)
	, m_pChargeThree(nullptr)
	, m_pChargeTwo(nullptr)
	, m_pChargeOne(nullptr)
	, m_pChargeZero(nullptr)
{
	m_pTargetPosition = pPos;
	Setup();
	
}


CUICharge::~CUICharge()
{
	SafeDelete(m_pChargeFive);
	SafeDelete(m_pChargeFour);
	SafeDelete(m_pChargeThree);
	SafeDelete(m_pChargeTwo);
	SafeDelete(m_pChargeOne);
	SafeDelete(m_pChargeZero);
}

void CUICharge::Setup()
{
	m_pChargeZero = new CUIChargeZero(m_pTargetPosition);

	m_pChargingBoard = new CUIChargeOne(m_pTargetPosition);;

	AddChild(m_pChargingBoard);
	InvertActive();
}

void CUICharge::UpdateCharging()
{
	float temp = m_fMaxThrowPower / 5.0f;

	if (temp * 1 > *m_pfThrowPower)
	{
		if (m_pChargeZero)
			m_pChargingBoard = m_pChargeZero;
	}
	else if (temp * 2 > *m_pfThrowPower)
	{
		if (m_pChargeOne)
			m_pChargingBoard = m_pChargeOne;
		else
		{
			m_pChargeOne = new CUIChargeOne(m_pTargetPosition);
			m_pChargingBoard = m_pChargeOne;

		}
			
	}
	else if (temp * 3 > *m_pfThrowPower)
	{
		if (m_pChargeTwo)
			m_pChargingBoard = m_pChargeTwo;
		else
		{
			m_pChargeTwo = new CUIChargeTwo(m_pTargetPosition);
			m_pChargingBoard = m_pChargeTwo;
		}
	}
	else if (temp * 4 > *m_pfThrowPower)
	{
		if (m_pChargeThree)
			m_pChargingBoard = m_pChargeThree;
		else
		{
			m_pChargeThree = new CUIChargeThree(m_pTargetPosition);
			m_pChargingBoard = m_pChargeThree;
		}
	}
	else if (temp * 5 > *m_pfThrowPower)
	{
		if (m_pChargeFour)
			m_pChargingBoard = m_pChargeFour;
		else
		{
			m_pChargeFour = new CUIChargeFour(m_pTargetPosition);
			m_pChargingBoard = m_pChargeFour;
		}
	}
	else
	{
		if (m_pChargeFive)
			m_pChargingBoard = m_pChargeFive;
		else
		{
			m_pChargeFive = new CUIChargeFive(m_pTargetPosition);
			m_pChargingBoard = m_pChargeFive;
		}
	}
	
	if (m_pChargingBoard)
	{
		if (m_pChargingBoard->GetActive() == false)
		{
			InvertActive();
		}
	}

}
