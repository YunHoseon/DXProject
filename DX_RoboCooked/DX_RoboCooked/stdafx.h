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
#include <iostream>

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
#include <unordered_map>
using std::unordered_map;

#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;
#define SafeRelease(p) { if(p) p->Release(); p = NULL; }

#define SafeDelete(p) { if(p) delete p; p = NULL; }

#define SafeDeleteArray(p) { if(p) delete[] p; p = NULL; }

#define ELIPSE 0.000001f

#define BLOCK_SIZE 1.0f

#define WIDTH 12
#define HEIGHT 16

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
	float	fRaidus;
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



#include "CDebugSphere.h"
#include "CDebugCube.h"

#ifdef _DEBUG
	#ifdef UNICODE
	#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
	#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

