#pragma once

#define g_EventManager CEventManager::GetInstance()

class CEventListener;

enum class EEvent
{
	E_Tick,
	E_KeyPress,
	E_KeyRelease,
	E_TileMove
};

struct ST_KeyInputEvent
{
	WPARAM wKey;
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
