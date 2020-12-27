#pragma once
#include "CUIButton.h"

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
	CUIChargeBoard*		m_pChargeFive;
	CUIChargeBoard*		m_pChargeFour;
	CUIChargeBoard*		m_pChargeThree;
	CUIChargeBoard*		m_pChargeTwo;
	CUIChargeBoard*		m_pChargeOne;

	D3DXVECTOR3			m_vChargeUIPosition;


public:
	CUICharge(D3DXVECTOR3* pPos);
	~CUICharge();

public:
	void Setup() override;
	void UpdateCharging(float fThrowPower, float fMaxThrowPower);
};

