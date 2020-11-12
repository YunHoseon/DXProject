#pragma once
class CEventListener
{

public:
	virtual ~CEventListener();
	virtual void OnEvent(EEvent eEvent,void* _value) = 0;
};

