#include "stdafx.h"
#include "CMeshLoader.h"
#include "CStaticMesh.h"
bool CMeshLoader::LoadMesh(string sFilename, string sFolder, LPD3DXMESH* pMesh, vector<D3DMATERIAL9>& vecMaterial,
	vector<LPDIRECT3DTEXTURE9>& vecTexture)
{
	if (*pMesh)
		return false;
	string sFolderLink = sFolder + string("/");
	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtlBuffer = 0;

	DWORD numMtls = 0;
	HRESULT hr;

	D3DXLoadMeshFromXA
	(
		(sFolderLink + sFilename).c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&adjBuffer,
		&mtlBuffer,
		0,
		&numMtls,
		pMesh
	);
	
	if (mtlBuffer != 0 && numMtls != 0)
	{
		D3DXMATERIAL* pMtls = (D3DXMATERIAL*)mtlBuffer->GetBufferPointer();
		vecMaterial.resize(numMtls);
		for (vector<LPDIRECT3DTEXTURE9>::value_type  texture : vecTexture)
		{
			SafeRelease(texture);
		}
		vecTexture.resize(numMtls);
		for (int i = 0; i < numMtls; ++i)
		{
			pMtls[i].MatD3D.Ambient = pMtls[i].MatD3D.Diffuse;

			vecMaterial[i] = pMtls[i].MatD3D;
			if (pMtls[i].pTextureFilename)
			{
				vecTexture[i] = g_pTextureManager->GetTexture(sFolderLink + pMtls[i].pTextureFilename);
			}
			else
				vecTexture[i] = nullptr;
		}
	}
	SafeRelease(mtlBuffer);
	SafeRelease(adjBuffer);
	return true;
}

bool CMeshLoader::LoadMesh(string sFilename, string sFolder, CStaticMesh* pcSMesh)
{
	return LoadMesh(sFilename, sFolder, &pcSMesh->GetMesh(), pcSMesh->GetVecMaterial(), pcSMesh->GetVecTexture());
}
