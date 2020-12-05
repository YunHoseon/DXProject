#pragma once
#include "CActor.h"

class CTile;

class CField :
	public CActor
{
public:
	CField();
	virtual ~CField();

public:
	void Setup(int iWidth = 16,int iHeight = 12);
	void Render() override;
	void Update() override;
	void OnEvent(eEvent eEvent, void* _value) {};
	void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	void AddForce(const D3DXVECTOR3& vForce) override {}
private:
	vector<CTile*>					m_vecTile;
	D3DMATERIAL9					m_stMtlTile;
};

