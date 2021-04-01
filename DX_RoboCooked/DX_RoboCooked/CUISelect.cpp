#include "stdafx.h"
#include "CUISelect.h"


CUISelect::CUISelect(D3DXVECTOR2 vPos, string chStageID, float fTime)
	:m_fGameTime(fTime),
	m_sStageID(chStageID)
{
	m_vPosition = vPos;

}


CUISelect::~CUISelect()
{
}
