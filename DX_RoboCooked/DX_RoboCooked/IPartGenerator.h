#pragma once
class CParts;
class IPartGenerator
{
protected:	
	string		m_sID;
	virtual ~IPartGenerator() = default;
	virtual CParts* Make() = 0;

};

