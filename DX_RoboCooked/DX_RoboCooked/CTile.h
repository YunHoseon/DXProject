#pragma once
#include "CActor.h"

class CTile : public CActor
{
public:
	CTile();
	~CTile();
	void AddEvent(EEvent eEvent);

private:
	Synthesize(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	Synthesize(LPDIRECT3DTEXTURE9, m_PlaneTexture, PlaneTexture);

public:
	void Render() override;
	void Update() {};
};

