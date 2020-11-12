#include "stdafx.h"
#include "CBoxCollision.h"

#include "CSphereCollision.h"

CBoxCollision::CBoxCollision(D3DXVECTOR3 vOriginPos, D3DXVECTOR3 vSize, D3DXMATRIXA16* pmatWorld): ICollisionArea(),
		m_pmatWorldTM(pmatWorld)
{
	m_eType = EColideType::E_Box;

	m_vOriginCenterPos = vOriginPos;

	m_vOriginAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriginAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriginAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisHalfLen[0] = vSize.x * 0.5f;
	m_fAxisHalfLen[1] = vSize.y * 0.5f;
	m_fAxisHalfLen[2] = vSize.z * 0.5f;
}

CBoxCollision::~CBoxCollision()
{
}

void CBoxCollision::Render()
{
	vector<ST_PC_VERTEX> drawPoint;
	vector<ST_PC_VERTEX> drawVertex;
	ST_PC_VERTEX vertex;
	vertex.c = stColor[isCollide];
	//cout << c << endl;
	int plusMinus[2] = { 1, -1 };
	
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				vertex.p = m_vCenterPos
					+ (m_vAxisDir[0] * m_fAxisHalfLen[0] * plusMinus[i])
					+ (m_vAxisDir[1] * m_fAxisHalfLen[1] * plusMinus[j])
					+ (m_vAxisDir[2] * m_fAxisHalfLen[2] * plusMinus[k]);
				drawPoint.push_back(vertex);
			}
		}
	}
	//                4-------------0
	//              /|             /|
	//             / |            / |
	//            /  |           /  |
	//           5-------------1    |
	//           |   |         |    |
	//           |   6-------------2
	//           |  /          |  /
	//           | /           | /
	//           7-------------3
	//
	drawVertex.push_back(drawPoint[0]); drawVertex.push_back(drawPoint[1]);
	drawVertex.push_back(drawPoint[1]); drawVertex.push_back(drawPoint[3]);
	drawVertex.push_back(drawPoint[3]); drawVertex.push_back(drawPoint[2]);
	drawVertex.push_back(drawPoint[2]); drawVertex.push_back(drawPoint[0]);
	
	drawVertex.push_back(drawPoint[4]); drawVertex.push_back(drawPoint[5]);
	drawVertex.push_back(drawPoint[5]); drawVertex.push_back(drawPoint[7]);
	drawVertex.push_back(drawPoint[7]); drawVertex.push_back(drawPoint[6]);
	drawVertex.push_back(drawPoint[6]); drawVertex.push_back(drawPoint[4]);
	
	drawVertex.push_back(drawPoint[5]); drawVertex.push_back(drawPoint[1]);
	drawVertex.push_back(drawPoint[4]); drawVertex.push_back(drawPoint[0]);
	
	drawVertex.push_back(drawPoint[6]); drawVertex.push_back(drawPoint[2]);
	drawVertex.push_back(drawPoint[7]); drawVertex.push_back(drawPoint[3]);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, drawVertex.size() * 0.5f, &drawVertex[0], sizeof(ST_PC_VERTEX));
}

void CBoxCollision::Update()
{
	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3TransformNormal(&m_vAxisDir[i], &m_vOriginAxisDir[i], m_pmatWorldTM);
	}

	D3DXVec3TransformCoord(&m_vCenterPos, &m_vOriginCenterPos, m_pmatWorldTM);
}

bool CBoxCollision::CollideToBox(ICollisionArea* pTargetCollider)
{
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;
	const float cutOff = 0.999999f;
	bool existsParallelPair = false;
	isCollide = false;
	
	CBoxCollision* target = dynamic_cast<CBoxCollision*>(pTargetCollider);

	D3DXVECTOR3 D = target->m_vCenterPos - this->m_vCenterPos;
	if (D3DXVec3LengthSq(&D) > 4.5f)
		return false;
	
	for (int a = 0; a < 3; ++a)
	{
		for (int b = 0; b < 3; ++b)
		{
			cos[a][b] = D3DXVec3Dot(&this->m_vAxisDir[a], &target->m_vAxisDir[b]);

			absCos[a][b] = abs(cos[a][b]);

			if (absCos[a][b] > cutOff)
				existsParallelPair = true; // 직각이란 뜻
		}
		dist[a] = D3DXVec3Dot(&this->m_vAxisDir[a], &D);
		r = abs(dist[a]);

		r0 = this->m_fAxisHalfLen[a];
		r1 = target->m_fAxisHalfLen[0] * absCos[a][0] +
			target->m_fAxisHalfLen[1] * absCos[a][1] +
			target->m_fAxisHalfLen[2] * absCos[a][2];

		if (r > r0 + r1)
			return false;
	}

	for (int b = 0; b < 3; ++b)
	{
		r = abs(D3DXVec3Dot(&target->m_vAxisDir[b], &D));
		r0 = this->m_fAxisHalfLen[0] * absCos[0][b] +
			this->m_fAxisHalfLen[1] * absCos[1][b] +
			this->m_fAxisHalfLen[2] * absCos[2][b];
		r1 = target->m_fAxisHalfLen[b];

		if (r > r0 + r1)
			return false;
	}

	if (existsParallelPair)
	{
		isCollide = true;
		return true;
	}

	{
		{
			// : 0
			r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
			r0 = this->m_fAxisHalfLen[0] * absCos[2][0] + this->m_fAxisHalfLen[2] * absCos[0][0];
			r1 = this->m_fAxisHalfLen[1] * absCos[1][2] + this->m_fAxisHalfLen[2] * absCos[1][1];
			if (r > r0 + r1) return false;

			// : 1
			r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
			r0 = this->m_fAxisHalfLen[0] * absCos[2][1] + this->m_fAxisHalfLen[2] * absCos[0][1];
			r1 = this->m_fAxisHalfLen[0] * absCos[1][2] + this->m_fAxisHalfLen[2] * absCos[1][0];
			if (r > r0 + r1) return false;

			// : 2
			r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
			r0 = this->m_fAxisHalfLen[0] * absCos[2][2] + this->m_fAxisHalfLen[2] * absCos[0][2];
			r1 = this->m_fAxisHalfLen[0] * absCos[1][1] + this->m_fAxisHalfLen[1] * absCos[1][0];
			if (r > r0 + r1) return false;
		}


		{
			// : 3
			r = abs(dist[1] * cos[0][0] - dist[2] * cos[1][0]);
			r0 = this->m_fAxisHalfLen[0] * absCos[1][0] + this->m_fAxisHalfLen[1] * absCos[0][0];
			r1 = this->m_fAxisHalfLen[1] * absCos[2][2] + this->m_fAxisHalfLen[2] * absCos[2][1];
			if (r > r0 + r1) return false;

			// : 4
			r = abs(dist[1] * cos[0][1] - dist[2] * cos[1][1]);
			r0 = this->m_fAxisHalfLen[0] * absCos[1][1] + this->m_fAxisHalfLen[1] * absCos[0][1];
			r1 = this->m_fAxisHalfLen[0] * absCos[2][2] + this->m_fAxisHalfLen[2] * absCos[2][0];
			if (r > r0 + r1) return false;

			// : 5
			r = abs(dist[1] * cos[0][2] - dist[2] * cos[1][2]);
			r0 = this->m_fAxisHalfLen[0] * absCos[1][2] + this->m_fAxisHalfLen[1] * absCos[0][2];
			r1 = this->m_fAxisHalfLen[0] * absCos[2][1] + this->m_fAxisHalfLen[1] * absCos[2][0];
			if (r > r0 + r1) return false;
		}

		{
			// : 6
			r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
			r0 = this->m_fAxisHalfLen[1] * absCos[2][0] + this->m_fAxisHalfLen[2] * absCos[1][0];
			r1 = this->m_fAxisHalfLen[1] * absCos[0][2] + this->m_fAxisHalfLen[2] * absCos[0][1];
			if (r > r0 + r1) return false;

			// : 7
			r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
			r0 = this->m_fAxisHalfLen[1] * absCos[2][1] + this->m_fAxisHalfLen[2] * absCos[1][1];
			r1 = this->m_fAxisHalfLen[0] * absCos[0][2] + this->m_fAxisHalfLen[2] * absCos[0][0];
			if (r > r0 + r1) return false;

			// : 8
			r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
			r0 = this->m_fAxisHalfLen[1] * absCos[2][2] + this->m_fAxisHalfLen[2] * absCos[1][2];
			r1 = this->m_fAxisHalfLen[0] * absCos[0][1] + this->m_fAxisHalfLen[1] * absCos[0][0];
			if (r > r0 + r1) return false;
		}

	}

	if (r > r0 + r1) return false;

	return false;
}

bool CBoxCollision::CollideToSphere(ICollisionArea* pTargetCollider)
{
	isCollide = false;

	CSphereCollision* target = dynamic_cast<CSphereCollision*>(pTargetCollider);
	D3DXVECTOR3 vDist = target->GetCenter() - this->m_vOriginCenterPos;
	
	if (D3DXVec3LengthSq(&vDist) > (1.0f + target->GetRadius()) * (1.0f + target->GetRadius()))
		return false;

	D3DXPLANE stPlanes[6];
	
	
	return false;
}
