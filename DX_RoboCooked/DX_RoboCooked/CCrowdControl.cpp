#include "stdafx.h"
#include "CCrowdControl.h"

CCrowdControl::CCrowdControl():
	m_fDuration(0.0f),
	m_fElapsedTime(0.0f)
{
}

CCrowdControl::CCrowdControl(CCrowdControl* clone):
	m_fDuration(clone->m_fDuration),
	m_fElapsedTime(0)
{
}

CCrowdControl::~CCrowdControl()
{

}
