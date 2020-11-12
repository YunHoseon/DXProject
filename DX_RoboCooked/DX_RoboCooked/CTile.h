#pragma once
#include "CActor.h"

class CTile : public CActor
{
public:
	CTile();
	~CTile();


private:
	Synthesize(LPDIRECT3DTEXTURE9, m_PlaneTexture, PlaneTexture);
	Synthesize(ST_CUBE, m_stCube, Cube);
	Synthesize_Pass_by_Ref(LPD3DXMESH, m_pCubeTile, MeshCubeTile);
	

public:
	void Render() override;
	void Update() override;
	void AddEvent(EEvent eEvent);
	void OnEvent(EEvent eEvent, void* _value) override;
};

