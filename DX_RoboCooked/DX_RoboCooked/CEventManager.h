#pragma once

#define g_EventManager CEventManager::GetInstance()

class CEventListener;

enum class EEvent
{
	E_EventTile,
	E_EventNONE
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
	void Attach(EEvent eEvent,CEventListener* _observer);
	bool Detach(EEvent eEvent, CEventListener* _observer);
	void DetachAll(CEventListener* _observer);
	void Notify(void* _value);
	void CallEvent(EEvent eEvent, void* _value);
	void ErrorSend();

private:
	std::map<EEvent, std::set<CEventListener*>> m_mapEventMap;
	EEvent m_eEvent;
};
