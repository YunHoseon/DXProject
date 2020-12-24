// stdafx.cpp : source file that includes just the standard includes
// DX_RoboCooked.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

string CalMin(int sec)
{
	int a = sec / 60;
	if (a >= 10)
	{
		return std::to_string(a);
	}
	else
	{
		return "0" + std::to_string(a);
	}
}

string CalSec(int sec)
{
	int a = sec % 60;
	if (a >= 10)
	{
		return std::to_string(a);
	}
	else
	{
		return "0" + std::to_string(a);
	}
}
