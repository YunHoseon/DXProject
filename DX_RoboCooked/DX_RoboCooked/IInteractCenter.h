﻿#pragma once

class CParts;
class CCharacter;
class CPartCombinator;
class COutlet;
class CCrowdControl;
class ICollisionArea;
class CTornado;
enum class eSkill;

class IInteractCenter
{
public:
	virtual ~IInteractCenter() = default;
	virtual void GetInteractObject(CCharacter *pCharacter) = 0;
	virtual void AddParts(CParts *parts) = 0;
	virtual void DeleteParts(CParts *parts) = 0;
	//virtual void ThrowParts(CCharacter* pCharacter,CParts* parts, D3DXVECTOR3 vDir) = 0;
	virtual void CheckAroundCombinator(CPartCombinator *combinator) = 0;
	//virtual void SendPartsToOutlet(CParts* parts, COutlet* outlet) = 0;
	virtual void ToggleStop() = 0;
	virtual bool GetStop() = 0;
	virtual float GetTime() = 0;
	virtual void ApplyMonsterSkill(eSkill skill, float fDuration = 0) = 0;
	virtual void FinishSkill(eSkill skill) = 0;
	virtual bool CheckSpecificPartsID(string partsID) = 0;
	virtual D3DXVECTOR3 SelectRandomObject() = 0;
	virtual bool CheckDistanceToSelectedObject(D3DXVECTOR3 pos, float fSize) = 0;
	virtual void CheckCollideCharacterToSandpile(ICollisionArea *collison) = 0;
	virtual D3DXVECTOR3 GetRandomPartsPosition() = 0;
	virtual void DestroyPartsOnPosition(D3DXVECTOR3 pos) = 0;
	virtual string GetSceneID() = 0;
	virtual const vector<CCharacter *> &GetCharacters() = 0;
	virtual bool CheckWarning() = 0;
};