#pragma once
class CEventListener
{

public:
	virtual ~CEventListener();
	virtual bool OnEvent(eEvent eEvent, void* _value) { return true; } // false를 반환하면 해당 이벤트를 detach한다
};

