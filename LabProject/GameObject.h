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

	//상수 버퍼를 생성한다.
	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	//상수 버퍼의 내용을 갱신한다.
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();

	//게임 객체의 월드 변환 행렬에서 위치 벡터와 방향(x-축, y-축, z-축) 벡터를 반환한다.
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();
	
	//게임 객체의 위치를 설정한다.
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);
	
	//게임 객체를 로컬 x-축, y-축, z-축 방향으로 이동한다.void MoveStrafe(float fDistance = 1.0f);
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);
	
	//게임 객체를 회전(x-축, y-축, z-축)한다.
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);

	//게임 객체가 카메라에 보인는 가를 검사한다.
	bool IsVisible(CCamera* pCamera = nullptr);

	//모델 좌표계의 픽킹 광선을 생성한다.
	void GenerateRayForPicking(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View, XMFLOAT3* pxmf3PickRayOrigin, XMFLOAT3* pxmf3PickRayDirection);
	//카메라 좌표계의 한 점에 대한 모델 좌표계의 픽킹 광선을 생성하고 객체와의 교차를 검사한다.
	int PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View,	float* pfHitDistance);

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