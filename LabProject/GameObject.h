#pragma once
#include "Mesh.h"

class CShader;
class CCamera;

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

protected:
	XMFLOAT4X4 m_xmf4x4World;
	CMesh* m_pMesh{ nullptr };
	CShader* m_pShader{ nullptr };

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