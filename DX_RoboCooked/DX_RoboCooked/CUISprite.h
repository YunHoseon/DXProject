#pragma once
#include "cSpriteNode.h"
class CUISprite :
	public cSpriteNode
{

public:
	CUISprite(char* OffBtnPath,char* OnBtnPath, char* HoverBtnPath , D3DXVECTOR2 vPosition);
	~CUISprite();

	virtual void Setup(D3DXVECTOR2 vecTranslation);

};

