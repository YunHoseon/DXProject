#pragma once
#include "CScene.h"

class CUIMainScreen;
class CUIMaker;
class CUIControll;

class CMainScene :
	public CScene
{
private:
	CUIMainScreen*	m_pScreen;
	CUIMaker*		m_pMaker;
	CUIControll*	m_pControll;
public:
	CMainScene();
	~CMainScene();

public:
	void Init() override;
	void Render() override;
	void Update() override;
};

