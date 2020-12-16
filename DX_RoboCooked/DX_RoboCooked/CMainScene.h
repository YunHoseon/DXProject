#pragma once
#include "CScene.h"

class CUIMainScreen;
class CUIMaker;

class CMainScene :
	public CScene
{
private:
	CUIMainScreen*	m_pScreen;
	CUIMaker*		m_pMaker;
public:
	CMainScene();
	~CMainScene();

public:
	void Init() override;
	void Render() override;
	void Update() override;
};

