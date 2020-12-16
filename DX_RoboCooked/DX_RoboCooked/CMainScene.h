#pragma once
#include "CScene.h"

class CUIMainScreen;

class CMainScene :
	public CScene
{
private:
	CUIMainScreen*	m_pScreen;
public:
	CMainScene();
	~CMainScene();

public:
	void Init() override;
	void Render() override;
	void Update() override;
};

