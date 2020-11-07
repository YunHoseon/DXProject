#pragma once
class CObserver
{
protected:
	std::set<EEvent> m_setSubsEvent;

public:
	virtual ~CObserver();
	void Subscribe(EEvent eEvent);
	void UnSubscribe(EEvent eEvent);
	virtual void OnEvent(EEvent eEvent,void* _value) = 0;
};

