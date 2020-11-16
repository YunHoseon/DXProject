#pragma once
class IPartGenerator
{
protected:
	int m_iID;
	virtual void Make() = 0;
};

