#pragma once
#include "CEventListener.h"
class CActor;
class CEventListener;

class CCrowdControl
{
protected:
	float m_fDuration;
	float m_fElapsedTime;
public:
	CCrowdControl();
	explicit CCrowdControl(CCrowdControl* clone);
	virtual ~CCrowdControl();
	virtual string GetID() = 0;

	virtual CCrowdControl* Clone() = 0;
	virtual float ReverseRotate() { return 0; }
	virtual float MultiplySpeed() { return 1.0f; }
	virtual void Render() = 0;
	virtual bool IsOverlapable() { return false; }
	virtual bool IsMovable() { return true; }
	virtual bool IsProtected() { return false; }
	virtual bool StopWithParts() { return false; }

	virtual bool IsEnd()
	{
		if(m_fDuration == 0.0f)
			return false;

		m_fElapsedTime += g_pTimeManager->GetElapsedTime();
		if (m_fElapsedTime >= m_fDuration)
			return true;
		return false;
	}
	virtual void SetDuration(float duration) { m_fDuration = duration; }
	virtual void SetTarget(D3DXVECTOR3* target) {}
};

#include "CCCSpeedDown.h"
#include "CCCReverseKey.h"
#include "CCCStopMove.h"
#include "CCCNone.h"
#include "CCCSlowAndStop.h"