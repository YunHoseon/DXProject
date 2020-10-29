#include "stdafx.h"
#include "CRandomGenerator.h"


CRandomGenerator::CRandomGenerator() : rd(), gen(rd())
{
	
}

CRandomGenerator::~CRandomGenerator()
{
}

// Max도 생성범위에 포함됨
void CRandomGenerator::GenIntArray(vector<int>& vecInt, int nVecSize, int nMin, int nMax)
{
	std::uniform_int_distribution<int> dis(nMin, nMax);
	vecInt.resize(nVecSize);
	for (size_t i = 0; i < nVecSize; i++)
		vecInt[i] = dis(gen);
}

// Max도 생성범위에 포함됨
int CRandomGenerator::GenInt(int nMin, int nMax)
{
	std::uniform_int_distribution<int> dis(nMin, nMax);
	return dis(gen);
}
