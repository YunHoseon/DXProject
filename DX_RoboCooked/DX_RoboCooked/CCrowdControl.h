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
};
