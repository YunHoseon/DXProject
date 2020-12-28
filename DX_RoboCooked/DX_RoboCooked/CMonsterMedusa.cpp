#include "stdafx.h"
#include "CMonsterMedusa.h"

#include "CSkinnedMesh.h"
#include "CSphereCollision.h"

CMonsterMedusa::CMonsterMedusa(IInteractCenter *pInteractCenter) : CMonster(pInteractCenter), m_nDestroyPartsPosition(0, 0, 0), m_pSkillAnim_1(nullptr)
{
	m_fFirstSkillConditionTime = 40.0f;
	m_fUltimateSkillConditionTime = 280.0f;
	//m_fUltimateSkillConditionTime = 295.0f;
	m_sSpecificPartsID = "B04";
	m_debugName = "medusa";
	ChooseSkillCondition();

	vector<D3DXVECTOR3> vecProjVertex, vecTrans;
	vecProjVertex.push_back(D3DXVECTOR3(-0.7, -0.7, 0.5));
	vecProjVertex.push_back(D3DXVECTOR3(-0.7, 0.2, 0.5));
	vecProjVertex.push_back(D3DXVECTOR3(0.7, 0.2, 0.5));
	vecProjVertex.push_back(D3DXVECTOR3(0.7, -0.7, 0.5));
	vecTrans.resize(4);

	D3DXVECTOR3 vTrans;

	D3DXMATRIXA16 matView, matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	string skillname = "medusa_skill_2_", sTemp;
	for (int i = 0; i < vecProjVertex.size(); ++i)
	{
		D3DXVec3Unproject(&vecTrans[i], &vecProjVertex[i], nullptr, &matProj, &matView, nullptr);
		CSkinnedMesh *p = new CSkinnedMesh;
		sTemp = skillname + std::to_string(i + 1) + ".x";
		p->Load("data/model/monster", const_cast<char *>(sTemp.c_str()));
		m_vecSkillAnim_2.push_back(p);
	}
	D3DXVec3Unproject(&vTrans, &D3DXVECTOR3(0, -0.2, 0.5f), nullptr, &matProj, &matView, nullptr);

	m_pSkillAnim_1 = new CSkinnedMesh;
	m_pSkillAnim_1->Load("data/model/monster", "medusa_skill_1.x");

	D3DXVECTOR3 vLookAt(matView._21, matView._22, matView._23);

	float rot = -D3DXVec3Dot(&vLookAt, &D3DXVECTOR3(0, 0, 1));
	D3DXMATRIXA16 matScale, matTrans, matX, matY;
	D3DXMatrixScaling(&matScale, 0.01, 0.01, 0.01);
	D3DXMatrixRotationX(&matX, rot);
	D3DXMatrixTranslation(&matTrans, vTrans.x, vTrans.y, vTrans.z);
	m_matSkillAnim_1 = matScale * matX * matTrans;
	m_pSkillAnim_1->Update();
	m_pSkillAnim_1->GetAnimController()->SetTrackSpeed(0, 0.4);

	{
		m_vecMatSkillAnim_2.resize(4);
		for (int i = 0; i < 4; ++i)
		{
			D3DXVECTOR3 dir = vecTrans[i] + vLookAt, axis;
			D3DXVec3Normalize(&dir, &dir);

			D3DXVec3Cross(&axis, &vLookAt, &dir);
			D3DXMatrixRotationAxis(&matX, &axis, rot);
			D3DXMatrixTranslation(&matTrans, vecTrans[i].x, vecTrans[i].y, vecTrans[i].z);
			D3DXMatrixRotationY(&matY, i < 2 ? D3DX_PI / -2 : D3DX_PI / 2 + 0.5);
			m_vecMatSkillAnim_2[i] = matScale * matY * matX * matTrans;
			m_vecSkillAnim_2[i]->Update();
		}
	}
}

CMonsterMedusa::~CMonsterMedusa()
{
	SafeDelete(m_pSkillAnim_1);
	for (vector<CSkinnedMesh *>::value_type p : m_vecSkillAnim_2)
	{
		SafeDelete(p);
	}
}

void CMonsterMedusa::Render()
{
	if (m_stSkillUsing.isFirstSkill)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matSkillAnim_1);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pSkillAnim_1->Render(nullptr);
	}
	if (m_stSkillUsing.isSecondSkill)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		for (int i = 0; i < 4; ++i)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecMatSkillAnim_2[i]);
			m_vecSkillAnim_2[i]->Render(nullptr);
		}
	}
	if (m_stSkillUsing.isUltimateSkill)
	{
		m_cPartsDestroyer.Render();
	}
}

void CMonsterMedusa::Update()
{

	if (FirstSkillTriggered())
	{
		m_stSkillUsing.FirstSkillProperty = FirstSkill();
		m_stSkillUsing.isFirstSkill = true;
		m_pInteractCenter->ApplyMonsterSkill(FirstSkill(), FirstSkillTime());

		m_pSkillAnim_1->SetAnimationIndexBlend(0);
	}

	if (SecondSkillTriggered())
	{
		m_stSkillUsing.SecondSkillProperty = SecondSkill();
		m_stSkillUsing.isSecondSkill = true;
		ChooseSkillCondition();
		m_pInteractCenter->ApplyMonsterSkill(SecondSkill(), SecondSkillTime());

		for (int i = 0; i < 4; ++i)
		{
			m_vecSkillAnim_2[i]->SetAnimationIndexBlend(0);
		}
	}

	if (m_eSecondSkillEvent == eEvent::SpecificArea)
	{
		if (m_pInteractCenter->CheckDistanceToSelectedObject(m_vSpecificAreaPosition,m_fArriveSize))
		{
			m_isArrive = true;
		}
	}

	if (UltimateSkillTriggered())
	{
		m_stSkillUsing.UltimateSkillProperty = UltimateSkill();
		m_stSkillUsing.isUltimateSkill = true;
		m_pInteractCenter->ApplyMonsterSkill(UltimateSkill(), UltimateSkillTime());

		m_cPartsDestroyer.SetActive(m_nDestroyPartsPosition, 5.0f);
	}

	if (CheckDurationTimeFirstSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.FirstSkillProperty);
		m_stSkillUsing.FirstSkillProperty = eSkill::None;
	}

	if (CheckDurationTimeSecondSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.SecondSkillProperty);
		m_stSkillUsing.SecondSkillProperty = eSkill::None;
	}

	if (CheckDurationTimeUltimateSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.UltimateSkillProperty);
		m_stSkillUsing.UltimateSkillProperty = eSkill::None;
	}
	UpdateMonster();
}

void CMonsterMedusa::UpdateMonster()
{
	if (m_stSkillUsing.isFirstSkill)
	{
		m_pSkillAnim_1->Update();
	}
	if (m_stSkillUsing.isSecondSkill)
	{
		for (int i = 0; i < 4; ++i)
		{
			m_vecSkillAnim_2[i]->Update();
		}
	}
	if (m_stSkillUsing.isUltimateSkill)
	{
		m_pInteractCenter->DestroyPartsOnPosition(m_nDestroyPartsPosition);
	}
}

eSkill CMonsterMedusa::UltimateSkill()
{
	g_SoundManager->PlaySFX("medusa_ult");
	m_nDestroyPartsPosition = m_pInteractCenter->GetRandomPartsPosition();
	return eSkill::DestroyParts;
}
