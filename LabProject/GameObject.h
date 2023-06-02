#pragma once
#include "Mesh.h"

class CShader;
class CCamera;

struct MATERIAL
{
	XMFLOAT4 m_xmf4Ambient;
	XMFLOAT4 m_xmf4Diffuse;
	XMFLOAT4 m_xmf4Specular; //(r,g,b,a=power) 
	XMFLOAT4 m_xmf4Emissive;
};

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	UINT GetReflection() const { return m_nReflection; };
	CShader* GetShader() const { return m_pShader; };

	void SetAlbedo(XMFLOAT4& xmf4Albedo) { m_xmf4Albedo = xmf4Albedo; }
	void SetReflection(UINT nReflection) { m_nReflection = nReflection; }
	void SetShader(CShader* pShader);

protected:
	//������ �⺻ ����
	XMFLOAT4 m_xmf4Albedo{ XMFLOAT4(1.0f,1.0f,1.0f,1.0) };
	//������ ��ȣ
	UINT m_nReflection{ 0 };
	//������ ���G�ƿ� �������ϱ� ���� ���̴�
	CShader* m_pShader{ nullptr };

private:
	int m_nReferences{ 0 };
};

////////////////////////////////////////////////////////////////////////////////////////////////

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	void ReleaseUploadBuffers();

	virtual void SetMesh(CMesh* pMesh);
	virtual void SetShader(CShader* pShader);

	virtual void Update(float fTimeElapsed);
	virtual void OnPrepareRender();
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	void Rotate(XMFLOAT3* pxmf3Axis, float fAngle);

	//��� ���۸� �����Ѵ�.
	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	//��� ������ ������ �����Ѵ�.
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();

	//���� ��ü�� ���� ��ȯ ��Ŀ��� ��ġ ���Ϳ� ����(x-��, y-��, z-��) ���͸� ��ȯ�Ѵ�.
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	//���� ��ü�� ��ġ�� �����Ѵ�.
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	void SetMaterial(CMaterial* pMaterial);
	void SetMaterial(UINT nReflection);

	//���� ��ü�� ���� x-��, y-��, z-�� �������� �̵��Ѵ�.void MoveStrafe(float fDistance = 1.0f);
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);

	//���� ��ü�� ȸ��(x-��, y-��, z-��)�Ѵ�.
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);

protected:
	XMFLOAT4X4 m_xmf4x4World;
	CMesh* m_pMesh{ nullptr };
	CMaterial* m_pMaterial{ nullptr };	//���� ��ü�� ���̴��� ������ �ʰ� ������ ������.

private:
	int m_nReferences {};

};

////////////////////////////////////////////////////////////////////////////////////////////////

class CRotatingObject : public CGameObject
{
public:
	CRotatingObject();
	virtual ~CRotatingObject();

	void SetRotationSpeed(float fRotationSpeed);
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis);

	virtual void Update(float fTimeElapsed) override;

private:
	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;
};