#include "stdafx.h"
#include "CSkinnedMesh.h"
#include "CAllocateHierachy.h"
#include "CSkinnedMeshManager.h"

CSkinnedMesh::CSkinnedMesh():
	m_pRoot(nullptr),
	m_pAnimController(nullptr),
	m_fBlendTime(0.1f),
	m_fPassedBlendTime(0.0f),
	m_isAnimBlend(false),
	m_dAnimPeriod(0),
	m_fAnimTime(0),
	m_isInputOn(true), m_nCurrentAnimIndex(0),
	m_vMin(g_vZero),
	m_vMax(g_vZero),
	m_pmatWorldTM(nullptr)
{
}

CSkinnedMesh::~CSkinnedMesh()
{
	CAllocateHierachy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SafeRelease(m_pAnimController);
}

void CSkinnedMesh::Setup(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath = sFullPath + "/" + szFile;

	CAllocateHierachy ah;
	ah.SetFolder(szFolder);
	
	D3DXLoadMeshHierarchyFromXA
	(
		sFullPath.c_str(), 
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah, 
		NULL, 
		&m_pRoot, 
		&m_pAnimController
	);

	SetupBoneMatrixPtrs(m_pRoot);
}

void CSkinnedMesh::Update()
{
	if (m_isAnimBlend)
	{
		m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();
		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAnimBlend = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackEnable(1, false);
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}
	
	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	Update((ST_BONE*)m_pRoot, m_pmatWorldTM);
	UpdateSkinnedMesh(m_pRoot);

	m_fAnimTime += g_pTimeManager->GetElapsedTime();
	if (m_fAnimTime + m_fBlendTime >= m_dAnimPeriod)
	{
		//m_isInputOn = true;
		//SetAnimationIndexBlend(IDLE);
	}
	 
}

void CSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;

	if(pParent)
	{
		pBone->CombinedTransformationMatrix *= ((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}

	if(pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}

	if(pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}
}

void CSkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	if (pFrame == nullptr)
		pFrame = m_pRoot;

	ST_BONE*		pBone = (ST_BONE*)pFrame;

	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if(pBoneMesh->MeshData.pMesh)
		{
			//g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);
			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); ++i)
			{
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
		Render(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		Render(pFrame->pFrameSibling);
}

void CSkinnedMesh::RenderWithShadow(LPD3DXFRAME pFrame)
{
	if (pFrame == nullptr)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{
			//g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);
			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); ++i)
			{
				g_pRenderShadowManager->GetApplyShadowShader()->SetTexture("DiffuseMap_Tex", pBoneMesh->vecTexture[i]);
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				g_pRenderShadowManager->GetApplyShadowShader()->CommitChanges();
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
		RenderWithShadow(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		RenderWithShadow(pFrame->pFrameSibling);
}

void CSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if(pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot, pSkinInfo->GetBoneName((i)));

				pBoneMesh->ppBoneMatrixPtrs[i] = &(pBone->CombinedTransformationMatrix);
			}
		}
	}

	if(pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}
	if (pFrame->pFrameSibling)
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
}

void CSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if(pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;

			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}

		BYTE * src = NULL;
		BYTE* dest = NULL;
		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (LPVOID*)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}

	if (pFrame->pFrameFirstChild)
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	
	if (pFrame->pFrameSibling)
		UpdateSkinnedMesh(pFrame->pFrameSibling);
}

void CSkinnedMesh::SetAnimationIndex(int nIndex)
{
	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex >= num) nIndex = nIndex % num;
	
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	//m_pAnimController->ResetTime();
	m_pAnimController->GetPriorityBlend();
	m_nCurrentAnimIndex = nIndex;
	m_dAnimPeriod = pAnimSet->GetPeriod();
}

void CSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	//if (!m_isInputOn)
	//	return;
	
	m_isAnimBlend = true;
	m_fPassedBlendTime = 0.0f;

	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex >= num) nIndex = nIndex % num;
	
	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC	stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);
	
	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);

	//if(pPrevAnimSet == pNextAnimSet)
	//{
	//	SafeRelease(pPrevAnimSet);
	//	SafeRelease(pNextAnimSet);
	//	return;
	//}

	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);
	
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackPosition(0, 0.0f);

	m_dAnimPeriod = pNextAnimSet->GetPeriod();
	m_fAnimTime = 0.0f;
	
	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	//if (nIndex == IDLE)
	//	m_isInputOn = true;
	//else
	//	m_isInputOn = false;
	m_nCurrentAnimIndex = nIndex;
	SafeRelease(pPrevAnimSet);
	SafeRelease(pNextAnimSet);
}

CSkinnedMesh::CSkinnedMesh(char* szFolder, char* szFileName) : CSkinnedMesh()
{
	CSkinnedMesh* pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFileName);

	m_pRoot = pSkinnedMesh->m_pRoot;
	
	m_vMin = pSkinnedMesh->m_vMin;
	m_vMax = pSkinnedMesh->m_vMax;

	pSkinnedMesh->m_pAnimController->CloneAnimationController(
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
		pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
		pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
		&m_pAnimController);
}

void CSkinnedMesh::Load(char* szFolder, char* szFileName)
{
	CAllocateHierachy ah;
	ah.SetFolder(szFolder);
	string sFullPath(szFolder);
	sFullPath += string("/") + szFileName;

	D3DXLoadMeshHierarchyFromXA(sFullPath.c_str(), D3DXMESH_MANAGED, g_pD3DDevice, &ah, nullptr, (LPD3DXFRAME*)&m_pRoot, &m_pAnimController);

	m_vMax = ah.GetMax();
	m_vMin = ah.GetMin();

	if (m_pRoot)
		SetupBoneMatrixPtrs(m_pRoot);
}

void CSkinnedMesh::Destroy()
{
	CAllocateHierachy ah;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRoot, &ah);
}

void CSkinnedMesh::UpdateAndRender()
{
	if (m_pAnimController)
		m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), nullptr);

	if(m_pRoot)
	{
		Update((ST_BONE*)m_pRoot, m_pmatWorldTM);
		Render(m_pRoot);
	}
}

void CSkinnedMesh::Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent)
{
	if (pCurrent == nullptr)
		pCurrent = (ST_BONE*)m_pRoot;

	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;

	if(pmatParent)
	{
		pCurrent->CombinedTransformationMatrix = pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if (pCurrent->pFrameSibling)
		Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);

	if (pCurrent->pFrameFirstChild)
		Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
}

void CSkinnedMesh::SetRandomTrackPosition()
{
	CRandomNumberGenerator r;
	m_pAnimController->SetTrackPosition(0, r.GenInt(0,99) / 10.0f);
}

void CSkinnedMesh::SetTransform(D3DXMATRIXA16* pmat)
{
	m_pmatWorldTM = pmat;
}

double CSkinnedMesh::GetCurrentAnimPeriod()
{
	return m_dAnimPeriod;
	/*LPD3DXANIMATIONSET curAnim;
	m_pAnimController->GetTrackAnimationSet(0, &curAnim);
	return curAnim->GetPeriod();*/
}
