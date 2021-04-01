#pragma once
#include "CScene.h"

class CUIMainScreen;
class CUIMaker;
class CUIControll;
class CUIStageSelect;

class CMainScene :
	public CScene
{
private:
	CUIMainScreen*	m_pScreen;
	CUIMaker*		m_pUIMaker;
	CUIControll*	m_pUIControll;
	CUIStageSelect* m_pUIStageSelect;
public:
	CMainScene();
	~CMainScene();

public:
	void Init() override;
	void Render() override;
	void Update() override;
};

