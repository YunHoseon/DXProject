#include "stdafx.h"
#include "CActor.h"



CActor::CActor()
{
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);

	

}


CActor::~CActor()
{
}
