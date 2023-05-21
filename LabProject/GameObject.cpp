#include "stdafx.h"
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"

CGameObject::CGameObject()
{
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
}

CGameObject::~CGameObject()
{
	if (m_pMesh)
	{
		m_pMesh->Release();
	}

	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CGameObject::ReleaseUploadBuffers()
{
}


void CGameObject::SetMesh(CMesh* pMesh)
{
	if (m_pMesh)
	{
		m_pMesh->Release();
	}

	m_pMesh = pMesh;
	
	if (m_pMesh)
	{
		m_pMesh->AddRef();
	}
}

void CGameObject::SetShader(CShader* pShader)
{
	if (m_pShader)
	{
		m_pShader->Release();
	}

	m_pShader = pShader;

	if (m_pShader)
	{
		m_pShader->AddRef();
	}
}

void CGameObject::Update(float fTimeElapsed)
{
	//���� ���۸� ���� ���ε� ���۸� �Ҹ��Ų��.
	if (m_pMesh)
	{
		m_pMesh->ReleaseUploadBuffers();
	}
}

void CGameObject::OnPrepareRender()
{
}

void CGameObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender();
	
	if (m_pShader)
	{
		//���� ��ü�� ���� ��ȯ ����� ���̴��� ��� ���۷� ����(����)�Ѵ�.
		m_pShader->UpdateShaderVariable(pd3dCommandList, &m_xmf4x4World);
		m_pShader->Render(pd3dCommandList, pCamera);
	}

	if (m_pMesh)
	{
		m_pMesh->Render(pd3dCommandList);
	}
}

void CGameObject::Rotate(XMFLOAT3* pxmf3Axis, float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(pxmf3Axis), XMConvertToRadians(fAngle));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

////////////////////////////////////////////////////////////////////////////////////////////////

CRotatingObject::CRotatingObject()
	: m_xmf3RotationAxis{XMFLOAT3{0.0f, 1.0f, 0.0f}}
	, m_fRotationSpeed{ 90.0f }
{
}

CRotatingObject::~CRotatingObject()
{
}

void CRotatingObject::SetRotationSpeed(float fRotationSpeed)
{
	m_fRotationSpeed = fRotationSpeed;
}

void CRotatingObject::SetRotationAxis(XMFLOAT3 xmf3RotationAxis)
{
	m_xmf3RotationAxis = xmf3RotationAxis;
}

void CRotatingObject::Update(float fTimeElapsed)
{
	CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
}
