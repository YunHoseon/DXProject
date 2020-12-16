#pragma once
#include "CUI.h"

class CUITexture :
	public CUI
{
private:
	LPD3DXSPRITE		m_Sprite;

	LPDIRECT3DTEXTURE9	m_ActiveTexture;
	LPDIRECT3DTEXTURE9	m_DisabledTexture;
	LPDIRECT3DTEXTURE9	m_HoverTexture;

	D3DXIMAGE_INFO		m_ActiveInfo;
	D3DXIMAGE_INFO		m_DisabledInfo;
	D3DXIMAGE_INFO		m_HoverInfo;

public:
	CUITexture(char* DisabledPath , char* ActivePath, char* HoverPath,D3DXVECTOR2 vPos);
	~CUITexture();

	void Update() override;
	void Render() override;
	void RenderTexture(eUIState state);
};

