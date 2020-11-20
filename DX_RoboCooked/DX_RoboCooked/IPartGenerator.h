#pragma once
class CParts;
class IPartGenerator
{
protected:	
	int			m_nID;
	virtual ~IPartGenerator() = default;
	virtual CParts* Make() = 0;
};

