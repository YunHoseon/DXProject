#include "stdafx.h"
#include "CUITrafficLight.h"
#include "CUITrafficLightBoard.h"
#include "CUITrafficLightOneBoard.h"
#include "CUITrafficLightTwoBoard.h"
#include "CUITrafficLightThreeBoard.h"
#include "CUITrafficLightFourBoard.h"
#include "CUITrafficLightFiveBoard.h"
#include "CUILight.h"


CUITrafficLight::CUITrafficLight(IInteractCenter* pInteractCenter, int nSize)
			: CUIButton(pInteractCenter)
			, m_nCompleteBluePrintCount(0)
			, m_pLightBoard(nullptr)
{

	g_EventManager->Attach(eEvent::CompleteBluePrint, this);
	g_EventManager->Attach(eEvent::UnCompleteBluePrint, this);

	switch (nSize)
	{
	case 1:
		m_pLightBoard = new CUITrafficLightOneBoard;
		break;
	case 2:
		m_pLightBoard = new CUITrafficLightTwoBoard;
		break;
	case 3:
		m_pLightBoard = new CUITrafficLightThreeBoard;
		break;
	case 4:
		m_pLightBoard = new CUITrafficLightFourBoard;
		break;
	case 5:
		m_pLightBoard = new CUITrafficLightFiveBoard;
		break;
	default:
		m_pLightBoard = new CUITrafficLightFiveBoard;
		break;
	}
	AddChild(m_pLightBoard);

	Setup();
	InvertActive();

}


CUITrafficLight::~CUITrafficLight()
{
}

void CUITrafficLight::Setup()
{
	CUILight* light = nullptr;
	for (int i = 0; i < m_pLightBoard->GetLightCount(); i++)
	{
		light = new CUILight(m_pLightBoard->GetLightPosition(i));
		m_pLightBoard->AddChild(light);
	}
}

bool CUITrafficLight::OnEvent(eEvent eEvent, void* _value)
{
	if (!m_isActive)
		return true;
	switch (eEvent)
	{
	case eEvent::CompleteBluePrint:
		AddCompleteBluePrintCount();
		break;
	case eEvent::UnCompleteBluePrint:
		removeCompleteBluePrintCount();
		break;
	default:
		return true;
		break;
	}
	m_pLightBoard->SetActiveUIState(m_nCompleteBluePrintCount);
	return true;
}
