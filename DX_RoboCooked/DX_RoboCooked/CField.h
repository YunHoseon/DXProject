#pragma once
#include "CActor.h"
#include "CTile.h"


class CField :
	public CActor
{
public:
	CField();
	~CField();

private:
	vector<CTile*> m_vecTile;
	
};

