#pragma once
#include "CUI.h"

class CUI;
class CUITexture;
class CUIText;

class CUIPause :
	public CUI
{
private:
	std::list<CUI*> m_listUIchildren;

public:
	CUIPause();
	~CUIPause();
	
	void Setup();
	void Update();
	void Render();


public:
	void Add(CUI *component) override;
	void Remove(CUI *component) override;



};

