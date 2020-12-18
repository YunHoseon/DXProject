#pragma once
#include "CUI.h"

class CUITexture :
	public CUI
{
protected:
	LPD3DXSPRITE		m_Sprite;

	LPDIRECT3DTEXTURE9	m_ActiveTexture;
	LPDIRECT3DTEXTURE9	m_DisabledTexture;
	LPDIRECT3DTEXTURE9	m_HoverTexture;

	D3DXIMAGE_INFO		m_ActiveInfo;
	D3DXIMAGE_INFO		m_DisabledInfo;
	D3DXIMAGE_INFO		m_HoverInfo;

public:
	CUITexture(char* DisabledPath , char* ActivePath, char* HoverPath,D3DXVECTOR2 vPos);
	CUITexture(char * DisabledPath, char * ActivePath, char * HoverPath, D3DXVECTOR3* pPosition);
	~CUITexture();
	void Setup(char* DisabledPath, char* ActivePath, char* HoverPath);
	void Update() override;
	void Render() override;
	void RenderTexture(eUIState state);
};

