// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <cstdlib>
#include <time.h>

// TODO: reference additional headers your program requires here
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <set>
using std::set;
#include <list>
using std::list;
#include <assert.h>
#include <unordered_set>
using std::unordered_set;
#include <array>
using std::array;
#include <thread>
using std::thread;
#include <mutex>


#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "include/nlohmann/json.hpp"
using nlohmann::json;

extern HWND g_hWnd;

#define SafeRelease(p) { if(p) p->Release(); p = nullptr; }

#define SafeDelete(p) { if(p) delete p; p = nullptr; }

#define SafeDeleteArray(p) { if(p) delete[] p; p = nullptr; }

#define EPSILON 0.00001f

#define BLOCK_SIZE 1.0f

#define WIDTH 16
#define HEIGHT 12



const D3DXVECTOR3 g_vZero(0.f,0.f,0.f);
const D3DXMATRIXA16 g_matIdentity(
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
);
constexpr float g_fFramerate = 60;
constexpr float g_fBaseDeltaTime = 1 / g_fFramerate;
#define TimeRevision (g_pTimeManager->GetElapsedTime() * g_fFramerate)

struct ST_PC_VERTEX
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	ST_PC_VERTEX() : p(), c(0) {}
	//ST_PC_VERTEX(float _x, float _y, float _z) : p(_x, _y, _x), c(0) {}
	ST_PC_VERTEX(float _x, float _y, float _z, D3DCOLOR _c = 0) : p(_x, _y, _z), c(_c) {}
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
	ST_PN_VERTEX() : p(), n() {}
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
	ST_PNT_VERTEX() : p(), n(), t() {}
	//ST_PNT_VERTEX(float _x, float _y, float _z, D3DCOLOR _c = 0) : p(_x, _y, _z), c(_c) {}
};

struct ST_PNC_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE };
	ST_PNC_VERTEX() : p(), n(), c() {}
	//ST_PNT_VERTEX(float _x, float _y, float _z, D3DCOLOR _c = 0) : p(_x, _y, _z), c(_c) {}
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
	ST_PT_VERTEX() : p(), t() {}
	//ST_PNT_VERTEX(float _x, float _y, float _z, D3DCOLOR _c = 0) : p(_x, _y, _z), c(_c) {}
};

struct ST_POS_SAMPLE
{
	int         n;
	D3DXVECTOR3 v;
	ST_POS_SAMPLE()
		: n(0)
		, v(0, 0, 0)
	{}
};

struct ST_ROT_SAMPLE
{
	int            n;
	D3DXQUATERNION q;
	ST_ROT_SAMPLE()
		: n(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};

struct ST_SPHERE
{
	float			fRaidus;
	D3DXVECTOR3		vCenter;
	bool			isPicked;
	ST_SPHERE(): fRaidus(0), isPicked(false), vCenter(0,0,0)
	{
	}
};

struct ST_CUBE
{
	float			fLength;
	D3DXVECTOR3		vCenter;
	ST_CUBE() : fLength(0), vCenter(0, 0, 0){}
};

struct ST_KeyInputEvent
{
	WPARAM wKey;
};

struct ST_MouseEvent
{
	POINT pt;
};

struct ST_TravelDistanceEvent
{
	float fDistance;
};
struct ST_SetTimeEvent
{
	int nTime;
};

struct ST_TickEvent
{
	float fElapsedTime;
};
struct ST_PLAYER_INPUTKEY
{
	WPARAM moveFowardKey;
	WPARAM moveLeftKey;
	WPARAM moveBackKey;
	WPARAM moveRightKey;

	WPARAM interactableKey1;
	WPARAM interactableKey2;
	WPARAM interactableKey3;

	ST_PLAYER_INPUTKEY& operator=(const ST_PLAYER_INPUTKEY& key)
	{
		moveFowardKey = key.moveFowardKey;
		moveLeftKey = key.moveLeftKey;
		moveBackKey = key.moveBackKey;
		moveRightKey = key.moveRightKey;
		interactableKey1 = key.interactableKey1;
		interactableKey2 = key.interactableKey2;
		interactableKey3 = key.interactableKey3;

		return *this;
	}
};

extern string CalMin(int sec);
extern string CalSec(int sec);


#define Synthesize(varType, varName, funName)\
	protected: varType varName; \
	public : inline varType Get##funName(void) const {return varName;}\
	public : inline void Set##funName(varType var) {varName = var;}

#define Synthesize_Pass_by_Ref(varType, varName, funName)\
	protected: varType varName; \
	public : inline varType& Get##funName(void) {return varName;}\
	public : inline void Set##funName(varType& var) {varName = var;}


#define SafeAddRef(p) { if (p) p->AddRef(); }

#define Synthesize_Add_Ref(varType, varName, funName)\
	protected : varType varName;\
	public: virtual varType Get##funName(void) const {return varName;}\
			virtual void Set##funName(varType var) \
			{\
				if(varName != var)\
				{\
					SafeAddRef(var);\
					SafeRelease(varName);\
					varName = var;\
				}\
			}


#include "CMainGame.h"
#include "CDeviceManager.h"
#include "CTextureManager.h"
#include "CTimeManager.h"
#include "CFontManager.h"
#include "CSceneManager.h"
#include "CEventManager.h"
#include "InputManager.h"
#include "CSoundManager.h"
#include "CPartsManager.h"
#include "CUITextureManager.h"
#include "CStaticMeshManager.h"
#include "CThreadManager.h"
#include "CSaveLoadManager.h"
#include "CShaderManager.h"
#include "CRandomNumberGenerator.h"

#define __SLASH(x) /##x
#define __DOUBLE_SLASH __SLASH(/)

#ifdef _DEBUG
	#ifdef UNICODE
		#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
		#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif

	#define _DEBUG_COMMENT
	#define _RELEASE_COMMENT __DOUBLE_SLASH
	#include <iostream>
	using std::cout;
	using std::endl;
#else
	#define _DEBUG_COMMENT __DOUBLE_SLASH
	#define _RELEASE_COMMENT

//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif
//#define _DEBUG_COMMENT
//#define _RELEASE_COMMENT
//#include <iostream>
//using std::cout;
//using std::endl;
#endif