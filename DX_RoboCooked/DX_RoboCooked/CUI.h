#pragma once
class cSpriteNode;
class CUISprite;

class CUI
{
public:
	//struct Sprite
	//{
	//	D3DXVECTOR2 st_SpriteSize;
	//	D3DXVECTOR2 st_Position;
	//};
	//
public:
	CUI();
	virtual ~CUI();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void Move(D3DXVECTOR2 vMove);



	
public:
	cSpriteNode*		m_pRoot;
	D3DXMATRIXA16		m_matWorld;

	//vector<Sprite>	m_vecSprite;
	//vector<CUISprite*>  m_vecBtn;

	
	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR2			m_vSize;
	POINT				m_ptMouseClick;
	POINT				m_ptMouseMove;
	

};

