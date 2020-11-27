#pragma once
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"

class CUITexture;
class CUIText;

class CUIPause :
	public CUI
{
private:
	CUITexture*		m_pUITexture;
	CUIText*		m_pUIText;
public:
	CUIPause();
	~CUIPause();
};

