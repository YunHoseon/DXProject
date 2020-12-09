#include "stdafx.h"
#include "CRandomNumberGenerator.h"


CRandomNumberGenerator::CRandomNumberGenerator() : rd(), gen(rd())
{
	
}

CRandomNumberGenerator::~CRandomNumberGenerator()
{
}

// Max도 생성범위에 포함됨
void CRandomNumberGenerator::GenIntArray(vector<int>& vecInt, int nVecSize, int nMin, int nMax)
{
	std::uniform_int_distribution<int> dis(nMin, nMax);
	vecInt.resize(nVecSize);
	for (size_t i = 0; i < nVecSize; i++)
		vecInt[i] = dis(gen);
}

// Max도 생성범위에 포함됨
int CRandomNumberGenerator::GenInt(int nMin, int nMax)
{
	std::uniform_int_distribution<int> dis(nMin, nMax);
	return dis(gen);
}

float CRandomNumberGenerator::GenFloat(float fMin, float fMax)
{
	std::uniform_real_distribution<float> dis(fMin, fMax);
	return dis(gen);
}
