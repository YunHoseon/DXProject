#pragma once

#define g_EventManager CEventManager::GetInstance()

class CObserver;


enum class EEvent
{
	E_DEFAULT,
	E_ATTACK,
	E_SLEEP,
	E_NONE
};

struct ST_AttackEvent
{
	std::string name;
	int age;
	ST_AttackEvent():age(0){}
};

class CEventManager : public CSingleton<CEventManager>
{
public:
	CEventManager();
	~CEventManager();

public:
	void Attach(EEvent eEvent,CObserver* _observer);
	bool Detach(EEvent eEvent, CObserver* _observer);
	void Notify(void* _value);
	void CallEvent(EEvent eEvent, void* _value);
	void ErrorSend();

private:
	std::map<EEvent, std::vector<CObserver*>> m_mapEventMap;
	EEvent m_eEvent;


};


