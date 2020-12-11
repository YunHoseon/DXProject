#pragma once
#include "CInteractiveActor.h"
class CPharaohCoppin :
	public CInteractiveActor
{
	CStaticMesh* m_pSMesh;
public:
	CPharaohCoppin();
	~CPharaohCoppin();

	void Update() override;
	void Render() override;
};

