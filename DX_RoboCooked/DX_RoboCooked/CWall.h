#pragma once
#include "CActor.h"
class CTV;
class IInteractCenter;

class CWall :
	public CActor
{
private:
	int						m_nRotAngleX;
	//ID3DXMesh*				m_p3DText;
	CTV*					m_pTV;
	CStaticMesh*			m_pSMesh;
	vector<D3DXMATRIXA16>	m_vecMeshLocalMatrix;
	void Setup(float fWidth = 30, float fHeight = 6);
	
public:
	CWall(IInteractCenter* pIntaract, bool hasTV, float fWidth = 30, float fHeight = 6);
	~CWall();

	void Update() override;
	void Render() override;
	bool OnEvent(eEvent eEvent, void* _value) override;

	//void CreateFont();
	void ReleaseKey(void* _value);

	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
};

