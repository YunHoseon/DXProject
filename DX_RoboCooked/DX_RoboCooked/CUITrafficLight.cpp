#include "stdafx.h"
#include "CUITrafficLight.h"
#include "CUITrafficLightBoard.h"
#include "CUITrafficLightOneBoard.h"
#include "CUITrafficLightTwoBoard.h"
#include "CUITrafficLightThreeBoard.h"
#include "CUITrafficLightFourBoard.h"
#include "CUITrafficLightFiveBoard.h"


CUITrafficLight::CUITrafficLight(IInteractCenter* pInteractCenter, int nSize)
			: m_pInteractCenter(pInteractCenter)
			, m_nCompleteBluePrintCount(0)
{

	g_EventManager->Attach(eEvent::CompleteBluePrint, this);
	g_EventManager->Attach(eEvent::UnCompleteBluePrint, this);

	CUITrafficLightBoard* lightBoard = nullptr;

	switch (nSize)
	{
	case 1:
		lightBoard = new CUITrafficLightOneBoard;
		break;
	case 2:
		lightBoard = new CUITrafficLightTwoBoard;
		break;
	case 3:
		lightBoard = new CUITrafficLightThreeBoard;
		break;
	case 4:
		lightBoard = new CUITrafficLightFourBoard;
		break;
	case 5:
		lightBoard = new CUITrafficLightFiveBoard;
		break;
	default:
		lightBoard = new CUITrafficLightFiveBoard;
		break;
	}
	Add(lightBoard);

	Setup();

}


CUITrafficLight::~CUITrafficLight()
{
}

void CUITrafficLight::Setup()
{
	/*CUI* board = new CUIPauseBoard(D3DXVECTOR2(m_vPosition.x, m_vPosition.y), eBtnEvent::None);
	Add(board);

	CUI* mainBtn = new CUIMainButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 200), eBtnEvent::PauseMain);
	board->Add(mainBtn);

	CUI* closeBtn = new CUICloseButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 200), eBtnEvent::PauseClose);
	board->Add(closeBtn);

	CUI* ResetBtn = new CUIResetButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 500), eBtnEvent::PauseReset);
	board->Add(ResetBtn);

	CUI* EndBtn = new CUIEndButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 500), eBtnEvent::PauseEnd);
	board->Add(EndBtn);*/
}

void CUITrafficLight::OnEvent(eEvent eEvent, void * _value)
{
}
