#pragma once
#define g_pPartsManager CPartsManager::GetInstance()
class CParts;
struct ST_Parts_Attr
{
	string sID;
	string sFormula;
	//D3DXVECTOR3 vScale;
	float fMass;
	LPD3DXMESH	pMesh;
	LPDIRECT3DTEXTURE9	pTexture;
};
class CPartsManager : public CSingleton<CPartsManager>
{
private:
	friend class CSingleton<CPartsManager>;
	CPartsManager();
	~CPartsManager();
	map<string, CParts*>	m_mapParts;
	map<string, string>			m_mapFormula;
public:
	void Load();
	CParts* CreateParts(string sID);
	string GetIDFromFormula(string sFormula);
};
