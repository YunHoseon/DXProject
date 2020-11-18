#pragma once

class CParts;
class CCharacter;

class IInteractCenter
{
public:
	virtual ~IInteractCenter() = default;
	virtual void GetInteractObject(CCharacter* pCharacter) = 0;
	virtual void AddParts(CParts* parts) = 0;
	virtual void DownParts(CParts* parts, D3DXVECTOR3 vDir) = 0;
};
