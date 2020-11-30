#pragma once

class CStaticMesh;

class CMeshLoader
{
public:
	static bool LoadMesh(string sFilename, string sFolder, LPD3DXMESH* pMesh, vector<D3DMATERIAL9>& vecMaterial, vector<LPDIRECT3DTEXTURE9>& vecTexture);
	static bool LoadMesh(string sFilename, string sFolder, CStaticMesh* pcSMesh);
};
