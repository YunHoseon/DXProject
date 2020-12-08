#pragma once
#include "CActor.h"
class CSandDummy :
	public CActor
{
private:
	CStaticMesh* m_pSMesh;

public:
	CSandDummy(D3DXVECTOR3 vPosition);
	~CSandDummy();
	void Render() override;
	void Update() override;
};

