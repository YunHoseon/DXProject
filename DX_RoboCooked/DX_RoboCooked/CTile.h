#pragma once
#include "CActor.h"
enum class eTileType
{
	FlowSand,
	Stair,
	Water,
	Brick,
	Sand,
	Soil,
	ThickSand
};

class CTile : public CActor
{
public:
	CTile();
	virtual ~CTile();


protected:
	//Synthesize(LPDIRECT3DTEXTURE9, m_PlaneTexture, PlaneTexture);
	//Synthesize(ST_CUBE, m_stCube, Cube);
	//Synthesize_Pass_by_Ref(LPD3DXMESH, m_pCubeTile, MeshCubeTile);
	CStaticMesh* m_pSMesh;

public:
	virtual void Render() override;
	virtual void Update() override;
	virtual void AddEvent(eEvent eEvent);
	virtual bool OnEvent(eEvent eEvent, void* _value) override;

	virtual void AddAcceleration(const D3DXVECTOR3& vAccel) override {}
	virtual void AddForce(const D3DXVECTOR3& vForce) override {}

	Synthesize(eTileType, m_eTileType, TileType);

	void CreateShadowMap() override;
};

#include "CSand.h"
#include "CThickSand.h"
#include "CFlowSand.h"
#include "CWater.h"
#include "CSoil.h"
#include "CBrick.h"
#include "CStair.h"