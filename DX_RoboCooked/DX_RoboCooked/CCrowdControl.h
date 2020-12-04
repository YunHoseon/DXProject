#pragma once

class CCrowdControl
{
public:
	virtual ~CCrowdControl();

	virtual string& GetID() = 0;
	virtual float ReverseRotate() { return 0; }
	virtual float MultiplySpeed() { return 1.0f; }
	virtual void Render(D3DXVECTOR3& vPos) = 0;
	virtual bool IsOverlapable() { return false; }
	virtual bool IsMovable() { return true; }
	virtual bool IsProtected() { return false; }
	// 타겟을 지정하는 함수

	virtual bool IsEnd() { return false; }
	virtual CCrowdControl* Clone() = 0;
};

