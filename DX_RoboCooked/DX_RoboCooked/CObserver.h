#pragma once
class CObserver
{

public:
	virtual ~CObserver();
	virtual void OnEvent(EEvent eEvent,void* _value) = 0;
};

