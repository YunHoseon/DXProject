#pragma once
#include "CUIButton.h"
class CUIStageSelectPopUpBoard :
	public CUIButton
{
private:
	vector<D3DXVECTOR2>		m_vecSelectPosition;
	D3DXVECTOR2				m_vMainPosition;

	D3DXVECTOR2				m_vLeftPosition;
	D3DXVECTOR2				m_vRightPosition;

public:
	CUIStageSelectPopUpBoard(D3DXVECTOR2 vPos);
	~CUIStageSelectPopUpBoard();

public:
	void Setup() override;


	D3DXVECTOR2 GetSelectPosition(int i) 
	{
		if (i >= m_vecSelectPosition.size() || i<= 0)
			i = 0;
		return m_vecSelectPosition[i]; 
	}

	D3DXVECTOR2 GetMainPosition() { return m_vMainPosition; }

	D3DXVECTOR2 GetLeftPosition() { return m_vLeftPosition; }

	D3DXVECTOR2 GetRightPosition() { return m_vRightPosition; }
};

