#pragma once
class CParts;
class IPartGenerator
{
protected:
	int			m_nID;
	
	virtual CParts* Make() = 0;
};

