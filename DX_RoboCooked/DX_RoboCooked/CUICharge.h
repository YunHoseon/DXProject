#pragma once
#include "CUIButton.h"

class CUIChargeZero;
class CUIChargeOne;
class CUIChargeTwo;
class CUIChargeThree;
class CUIChargeFour;
class CUIChargeFive;
class CUIChargeBoard;

class CUICharge :
	public CUIButton
{
private:
	float*				m_pfThrowPower;
	float				m_fMaxThrowPower;
	CUIChargeBoard*		m_pChargingBoard;

	CUIChargeFive*		m_pChargeFive;
	CUIChargeFour*		m_pChargeFour;
	CUIChargeThree*		m_pChargeThree;
	CUIChargeTwo*		m_pChargeTwo;
	CUIChargeOne*		m_pChargeOne;
	CUIChargeZero*		m_pChargeZero;



public:
	CUICharge(D3DXVECTOR3* pPos,float* pfThrowPower , float fMaxThrowPower);
	~CUICharge();

public:
	void Setup() override;
	void UpdateCharging();
};

