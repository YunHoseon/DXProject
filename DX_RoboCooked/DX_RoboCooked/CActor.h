#pragma once
#include "CObserver.h"

class CActor : public CObserver
{
public:
	CActor();
	virtual  ~CActor();

protected:
	D3DXMATRIXA16 m_matS;
	D3DXMATRIXA16 m_matR;
	D3DXMATRIXA16 m_matT;
	//콜라이더 미추가

public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};

