#pragma once

#define g_EventManager CEventManager::GetInstance()

class CEventListener;

enum class eEvent
{
	None,
	Tick,
	KeyPress,
	KeyRelease,
	Player1KeyChange,
	Player2KeyChange,
	TileMove,
	PartsHold,
	SpinParts,
	PartsPut,
	PartsThrow,
	MouseClick,
	MouseHover,
	MouseRelease,
	ThrowParts,
	CrowdControl,
	VendingUse,
	CombinUse,
	SpecificArea,
	TravelDistance,
	DeleteTornado,
	CompleteBluePrint,
	UnCompleteBluePrint,
	PauseMain,
	PauseClose,
	PauseReset,
	PauseEnd,
	ClearMain,
	ClearNextStage,
	ClearSetTime,
	LoseMain,
	LoseReset,
	MainStart,
	MainControll,
	MainMaker,
	MainEvent,
	MainEnd,
	LoadingEnd,
	StageClose,
	MakerClose,
	ControllClose,
	ReadyBoard,
	CallWarning,
	SelectButton1,
	SelectButton2,
	SelectButton3,
	SelectButton4,
	SelectButton5,
	SelectButton6,
	SelectLeft,
	SelectRight
};


class CEventManager : public CSingleton<CEventManager>
{
private:
	friend CSingleton<CEventManager>;
	CEventManager();
	~CEventManager();

public:
	void Attach(eEvent eEvent,CEventListener* _observer);
	bool Detach(eEvent eEvent, CEventListener* _observer);
	void DetachAll(CEventListener* _observer);
	void CallEvent(eEvent eEvent, void* _value);
	void ErrorSend();

private:
	std::map<eEvent, std::set<CEventListener*>> m_mapEventMap;
	//eEvent m_eEvent;
};
