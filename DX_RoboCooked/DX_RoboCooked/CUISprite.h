#pragma once
#include "cSpriteNode.h"
class CUISprite :
	public cSpriteNode
{

public:
	CUISprite(char* OffBtnPath, char* OffFileName , char* OnBtnPath, char* OnFileName);
	~CUISprite();

	virtual void Setup(D3DXVECTOR2 vecTranslation);

};

