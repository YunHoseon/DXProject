#pragma once
class CEventListener
{

public:
	virtual ~CEventListener();
	virtual void OnEvent(eEvent eEvent,void* _value) = 0;
};

